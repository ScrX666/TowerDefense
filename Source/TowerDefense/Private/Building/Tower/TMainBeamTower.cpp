// Fill out your copyright notice in the Description page of Project Settings.


#include "Building/Tower/TMainBeamTower.h"

ATMainBeamTower::ATMainBeamTower()
{
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
		LaserBeam = GetWorld()->SpawnActor<ATLaserBeam>(BeamClass,BuildingMesh->GetSocketTransform(TEXT("BulletSocket")));
	}
	LaserBeam->Init(TargetMan);

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
	LaserBeam->Destroy();
	LaserBeam = nullptr;
}
