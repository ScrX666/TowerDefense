// Fill out your copyright notice in the Description page of Project Settings.


#include "Building/Tower/TMainBeamTower.h"

#include "Component/ActorComp/TBeamTowerState.h"

ATMainBeamTower::ATMainBeamTower()
{
	BeamTowerStateComp = CreateDefaultSubobject<UTBeamTowerState>(TEXT("BeamTowerStateComp"));
}

void ATMainBeamTower::OnConstruct(ATMainAttachBase* AttachBase)
{
	Super::OnConstruct(AttachBase);

}

void ATMainBeamTower::BeginPlay()
{
	Super::BeginPlay();
}

void ATMainBeamTower::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	// 动态加载数据
	// ShotTowerData = TDataTableManager::GetInstance()->GetShotTowerData(Name);
	// BulletClass = ShotTowerData.Bullet;
	BeamTowerStateComp->Init(Name);
}

void ATMainBeamTower::UpdateBeamDamage(const float NewDamage)
{
	if( LaserBeam)
	{
		LaserBeam->SetDamage(NewDamage);
	}
}

int32 ATMainBeamTower::GetCostCoins()
{
	return BeamTowerStateComp->GetCostCoins();
}

void ATMainBeamTower::Fire()
{
	if( TargetMan == nullptr)
		return ;

	
	Super::Fire();
	auto Socket = BuildingMesh->GetSocketByName(TEXT("BulletSocket"));
	if( Socket == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Socket NULL"));
		return ;
	}
	if( !LaserBeam && IsValid(BeamClass))
	{
		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.Owner = this;
		
		LaserBeam = GetWorld()->SpawnActor<ATLaserBeam>(BeamClass,BuildingMesh->GetSocketTransform(TEXT("BulletSocket")),ActorSpawnParameters);
	}
	LaserBeam->Init(TargetMan,BeamTowerStateComp->CurrentDamage);

}

void ATMainBeamTower::OnDestory()
{
	Super::OnDestory();
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
}

void ATMainBeamTower::TargetInRange()
{
	Super::TargetInRange();
	Fire();
}

void ATMainBeamTower::NoTargetInRange()
{
	Super::NoTargetInRange();
	if( LaserBeam)
	{
		LaserBeam->Destroy();
		LaserBeam = nullptr;
	}
}
void ATMainBeamTower::GetExp(int Exp)
{
	// Super::GetExp();
	BeamTowerStateComp->GetExp(Exp);
}
