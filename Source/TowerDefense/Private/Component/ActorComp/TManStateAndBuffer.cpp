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


// Sets default values for this component's properties
UTManStateAndBuffer::UTManStateAndBuffer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTManStateAndBuffer::DestorySelf(AActor* InstigatorActor)
{
	GetOwner()->Destroy();
}

// Called when the game starts
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
			OrignWalkSpeed = CharacterMovementComp->MaxWalkSpeed;
		}
	}

	
	// State
	// 注意顺序 被销毁后不再执行
	OnDead.AddDynamic(this,&UTManStateAndBuffer::AddCoinsAndExp);
	OnDead.AddDynamic(this,&UTManStateAndBuffer::DestorySelf);

	// Buffer
	
}


// Called every frame
void UTManStateAndBuffer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTManStateAndBuffer::ApplyHealthChange(AActor* Instigator,float Delta)
{
	CurrentHealth += Delta;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, ManState.MaxHealth);
	OnHealthChanged.Broadcast(Instigator,this, CurrentHealth,Delta);
	//TODO: 添加死亡事件
	if( CurrentHealth == 0)
		OnDead.Broadcast(Instigator);
}

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
	LatentActionInfo.ExecutionFunction = TEXT("DeActivePoison");
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

void UTManStateAndBuffer::ApplyPoisonDamage()
{
	UGameplayStatics::ApplyDamage(this->GetOwner(),PoisonDamage,
		UGameplayStatics::GetPlayerController(this,0),
		BufferInstigators[EManBufferType::E_Poison],
		UDamageType::StaticClass());
}

void UTManStateAndBuffer::ActiveBufferEffect(const FTManBuffer& Buffer, FName SocketName)
{
	if( !BufferNiagaraSystems.Contains(Buffer.BufferType))
	{
		auto Nia = UNiagaraFunctionLibrary::SpawnSystemAttached(
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

void UTManStateAndBuffer::DeActiveBufferEffect(const EManBufferType ManBufferType)
{
	if( BufferNiagaraSystems.Contains(ManBufferType))
	{
		BufferNiagaraSystems[ManBufferType]->SetAsset(nullptr);
		UE_LOG(LogTemp,Log,TEXT("DeActiveBufferEffect "));
	}
}
