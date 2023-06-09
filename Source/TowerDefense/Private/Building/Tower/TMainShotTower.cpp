// Fill out your copyright notice in the Description page of Project Settings.


#include "Building/Tower/TMainShotTower.h"

#include "BlueprintFunctionLibrary/TBlueprintFunctionLibrary.h"
#include "Component/ActorComp/TShotTowerState.h"
#include "Engine/StaticMeshSocket.h"
#include "Component/ActorComp/Tower/TAttackHandleComponent.h"
#include "Projectile/TMainBullet.h"

ATMainShotTower::ATMainShotTower()
{
	ShotTowerStateComp = CreateDefaultSubobject<UTShotTowerState>(TEXT("ShotTowerState"));
}

void ATMainShotTower::OnConstruct(ATMainAttachBase* AttachBase)
{
	Super::OnConstruct(AttachBase);
}

void ATMainShotTower::BeginPlay()
{
	Super::BeginPlay();
	for( const FTManBuffer& Buffer : ShotTowerStateComp->GetApplyBuffers())
	{
		ApplyBuffers.Add(Buffer);
	}
}

void ATMainShotTower::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if( !this || !ShotTowerStateComp) return ;
	// 动态加载数据
	ShotTowerStateComp->Init(Name);
	BulletClass = ShotTowerStateComp->GetBulletClass();
}

void ATMainShotTower::UpdateShotRate(float ShotRate)
{
	UE_LOG(LogTemp,Log,TEXT("UpdateShotRate %f"),ShotRate);
	if( AttackHandleComponent->TargetIsEmpty())
	{
		const float TimeRemain = FMath::Clamp(
		GetWorld()->GetTimerManager().GetTimerRemaining(FireTimerHandle),
		0.0f,
		MAX_flt);
		GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(FireTimerHandle,this,&ATMainShotTower::Fire,ShotRate, true,TimeRemain);
	}
}

int32 ATMainShotTower::GetCostCoins()
{
	return ShotTowerStateComp->GetCostCoins();
}

UTTowerStateComponent* ATMainShotTower::GetStateComp() const
{
	return ShotTowerStateComp;
}

void ATMainShotTower::Fire()
{
	const int32 ParallelAttackCount = AttackHandleComponent->GetParallelAttackCount();
	UE_LOG(LogTemp, Log, TEXT("ATMainShotTower Fire ParallelAttackCount %d"),ParallelAttackCount);
	for(int i = 0; i < ParallelAttackCount; i++)
	{
		ATManBase* TargetMan = AttackHandleComponent->GetAttackTarget(i);
		if( TargetMan == nullptr)
			continue;
		if( IsValid(BulletClass) == false)
		{
			UE_LOG(LogTemp,Warning,TEXT("Bullet NULL"));
		}
	
		Super::Fire();
		const auto Socket = BuildingMesh->GetSocketByName(TEXT("BulletSocket"));
		if( Socket == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Socket NULL"));
			return ;
		}
		// 播放发射音效

		UTBlueprintFunctionLibrary::PlayRandomSound(this,ShotTowerStateComp->GetShotSound(),this->GetActorLocation());

		// 生成子弹
		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.Owner = this;

		FTransform SocketTransform = BuildingMesh->GetSocketTransform(TEXT("BulletSocket"));
		const auto Bullet = GetWorld()->SpawnActor<ATMainBullet>(BulletClass, SocketTransform.GetLocation(),SocketTransform.Rotator(),ActorSpawnParameters);
		if( Bullet != nullptr)
		{
			Bullet->Init(TargetMan,ShotTowerStateComp->BulletSpeed,ShotTowerStateComp->CurrentDamage,ApplyBuffers);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("BulletClass NULL"));
		}
	}

}

void ATMainShotTower::OnDestory()
{
	Super::OnDestory();
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
}

void ATMainShotTower::TargetInRange()
{
	UE_LOG(LogTemp,Log,TEXT("TargetInRange ShotTowerStateComp->ShotRate %f"),ShotTowerStateComp->ShotRate);
	Super::TargetInRange();
	const float TimeRemain = FMath::Clamp(
		GetWorld()->GetTimerManager().GetTimerRemaining(FireTimerHandle),
		0.0f,
		MAX_flt);
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle,this,&ATMainShotTower::Fire,ShotTowerStateComp->ShotRate, true, TimeRemain);
}

void ATMainShotTower::NoTargetInRange()
{
	UE_LOG(LogTemp,Log,TEXT("NoTargetInRange"));
	Super::NoTargetInRange();
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
}

void ATMainShotTower::GetExp(int Exp)
{
	// Super::GetExp();
	ShotTowerStateComp->GetExp(Exp);
}



