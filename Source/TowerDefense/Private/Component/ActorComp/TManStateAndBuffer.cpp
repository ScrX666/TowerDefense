// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ActorComp/TManStateAndBuffer.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Building/Tower/TMainTower.h"
#include "Character/TManBase.h"
#include "Enum/EManBufferType.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GamePlay/TPlayerController.h"
#include "GamePlay/TPlayerState.h"
#include "Kismet/GameplayStatics.h"

void UTManStateAndBuffer::DestorySelf(AActor* InstigatorActor)
{
	ATManBase* Man = Cast<ATManBase>(GetOwner());
	if( Man)
	{
		Man->OnManDead();
	}
}

void UTManStateAndBuffer::BeginPlay()
{
	Super::BeginPlay();

	// 获取人物及其运动组件
	Owner = Cast<ATManBase>(GetOwner());
	if( Owner)
	{
		if( Cast<UCharacterMovementComponent>(Owner->GetMovementComponent()))
		{
			CharacterMovementComp = Cast<UCharacterMovementComponent>(Owner->GetMovementComponent());
		}
	}

	
	// State
	// 注意顺序 被销毁后不再执行
	OnDead.AddDynamic(this,&UTManStateAndBuffer::AddCoinsAndExp);
	OnDead.AddDynamic(this,&UTManStateAndBuffer::DestorySelf);

	// Buffer
	
}

void UTManStateAndBuffer::ApplyHealthChange(AActor* Instigator,float Delta)
{
	CurrentHealth += Delta;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, ManState.MaxHealth);
	OnHealthChanged.Broadcast(Instigator,this, CurrentHealth,Delta);

	// 死亡
	if( CurrentHealth == 0)
		OnDead.Broadcast(Instigator);
}
/*
 * 死亡后获得金币和经验
 */
void UTManStateAndBuffer::AddCoinsAndExp(AActor* InstigatorActor)
{
	UE_LOG(LogTemp,Log,TEXT("Destory Man AddCoins"));
	auto TPlayerControl = Cast<ATPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	// Get Coins
	if( TPlayerControl)
	{
		TPlayerControl->TPlayerState->AddCoins(ManState.Coins);
	}

	// Get Exp
	if( InstigatorActor && InstigatorActor->IsA<ATMainTower>())
	{
		Cast<ATMainTower>(InstigatorActor)->GetExp(ManState.Exp);
	}
}
/*
 * 激活Buff
 */
void UTManStateAndBuffer::ActivateBuffer(const TArray<FTManBuffer>& Buffers, AActor* Instigator)
{
	for( const FTManBuffer& Buffer : Buffers)
	{
		switch (Buffer.BufferType)
		{
		case EManBufferType::E_Ice:
			ActiveIce(Buffer);
			break;
		case EManBufferType::E_Poison:
			ActivePoison(Buffer);
			break;
		default: ;
		}

		// buff的施加者 方便进行coin和exp的结算
		if( BufferInstigators.Contains(Buffer.BufferType))
		{
			BufferInstigators[Buffer.BufferType] = Instigator;
		}
		else
		{
			BufferInstigators.Add(Buffer.BufferType,Instigator);
		}
	}
}

void UTManStateAndBuffer::ActiveIce(const FTManBuffer& Buffer)
{
	if( Owner)
	{
		// 初始化 初始速度
		if( MAX_flt == OrignWalkSpeed)
		{
			OrignWalkSpeed = CharacterMovementComp->MaxWalkSpeed;
		}
		
		if( CharacterMovementComp)
		{
			CharacterMovementComp->MaxWalkSpeed = OrignWalkSpeed * Buffer.EffectNum;
		}
	}

	ActiveBufferEffect(Buffer,FName(""));
	
	// Buffer 结束
	FLatentActionInfo LatentActionInfo;
	LatentActionInfo.Linkage = 0;
	LatentActionInfo.CallbackTarget = this;
	LatentActionInfo.ExecutionFunction = TEXT("DeActiveIce");
	LatentActionInfo.UUID = GetUniqueID() + static_cast<int32>(Buffer.BufferType);
	
	UKismetSystemLibrary::RetriggerableDelay(this, Buffer.DurationTime,LatentActionInfo);
}

void UTManStateAndBuffer::ActivePoison(const FTManBuffer& Buffer)
{
	if( !BufferTimerHandles.Contains( EManBufferType::E_Poison))
	{
		BufferTimerHandles.Add(EManBufferType::E_Poison);
	}
	PoisonDamage = Buffer.EffectNum;
	//设置持续伤害
	GetWorld()->GetTimerManager().ClearTimer(BufferTimerHandles[EManBufferType::E_Poison]);
	GetWorld()->GetTimerManager().SetTimer(BufferTimerHandles[EManBufferType::E_Poison],this,&UTManStateAndBuffer::ApplyPoisonDamage,0.1f,true,0.0f);

	ActiveBufferEffect(Buffer,FName(""));
	
	// Buffer 结束
	FLatentActionInfo LatentActionInfo;
	LatentActionInfo.Linkage = 0;
	LatentActionInfo.CallbackTarget = this;
	LatentActionInfo.ExecutionFunction = TEXT("DeActivePoison"); // 设置函数名
	LatentActionInfo.UUID = GetUniqueID() + 2;
	
	UKismetSystemLibrary::RetriggerableDelay(this, Buffer.DurationTime,LatentActionInfo);
}

void UTManStateAndBuffer::DeActiveIce()
{
	if( CharacterMovementComp)
		CharacterMovementComp->MaxWalkSpeed = OrignWalkSpeed;
	DeActiveBufferEffect(EManBufferType::E_Ice);
}

void UTManStateAndBuffer::DeActivePoison()
{
	GetWorld()->GetTimerManager().ClearTimer(BufferTimerHandles[EManBufferType::E_Poison]);
	DeActiveBufferEffect(EManBufferType::E_Poison);
}
/**
 * 施加持续伤害
 */
void UTManStateAndBuffer::ApplyPoisonDamage()
{
	UGameplayStatics::ApplyDamage(this->GetOwner(),PoisonDamage,
		UGameplayStatics::GetPlayerController(this,0),
		BufferInstigators[EManBufferType::E_Poison],
		UDamageType::StaticClass());
}
/*
 * 设置Buff的特效
 */
void UTManStateAndBuffer::ActiveBufferEffect(const FTManBuffer& Buffer, FName SocketName)
{
	if( !BufferNiagaraSystems.Contains(Buffer.BufferType))
	{
		const auto Nia = UNiagaraFunctionLibrary::SpawnSystemAttached(
			Buffer.NiagaraEffect,
			GetOwner()->GetRootComponent(),
			SocketName,
			FVector::ZeroVector,
			FRotator::ZeroRotator,
			EAttachLocation::KeepRelativeOffset,
			false);
		BufferNiagaraSystems.Add(Buffer.BufferType,Nia);
	}
	else
	{
		if(BufferNiagaraSystems[Buffer.BufferType]->GetAsset() != Buffer.NiagaraEffect)
		{
			BufferNiagaraSystems[Buffer.BufferType]->SetAsset( Buffer.NiagaraEffect);
			BufferNiagaraSystems[Buffer.BufferType]->ActivateSystem(true);
		}
	}
}
/*
 * 移除Buff的特效
 */
void UTManStateAndBuffer::DeActiveBufferEffect(const EManBufferType ManBufferType)
{
	if( BufferNiagaraSystems.Contains(ManBufferType))
	{
		BufferNiagaraSystems[ManBufferType]->SetAsset(nullptr);
		UE_LOG(LogTemp,Log,TEXT("DeActiveBufferEffect "));
	}
}
