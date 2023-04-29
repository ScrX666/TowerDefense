// Fill out your copyright notice in the Description page of Project Settings.


#include "Building/Tower/TMainShotTower.h"

#include "Engine/StaticMeshSocket.h"
#include "GamePlay/TDataTableManager.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile/TMainBullet.h"

ATMainShotTower::ATMainShotTower()
{
}

void ATMainShotTower::OnConstruct(ATMainAttachBase* AttachBase)
{
	Super::OnConstruct(AttachBase);

	
}

void ATMainShotTower::BeginPlay()
{
	Super::BeginPlay();
}

void ATMainShotTower::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	// 动态加载数据
	ShotTowerData = TDataTableManager::GetInstance()->GetShotTowerData(Name);
	BulletClass = ShotTowerData.Bullet;
}

void ATMainShotTower::Fire()
{
	if( TargetMan == nullptr)
		return ;
	if( IsValid(BulletClass) == false)
	{
		UE_LOG(LogTemp,Warning,TEXT("Bullet NULL"));
	}
	
	Super::Fire();
	auto Socket = BuildingMesh->GetSocketByName(TEXT("BulletSocket"));
	if( Socket == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Socket NULL"));
		return ;
	}
	// 播放发射音效
	if( ShotTowerData.ShotSound != nullptr)
	{
		UGameplayStatics::PlaySound2D(this,ShotTowerData.ShotSound);
	}
	auto Bullet = GetWorld()->SpawnActor<ATMainBullet>(BulletClass,BuildingMesh->GetSocketTransform(TEXT("BulletSocket")));
	if( Bullet != nullptr)
	{
		Bullet->Init(TargetMan);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("BulletClass NULL"));
	}

}

void ATMainShotTower::OnDestory()
{
	Super::OnDestory();
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
}

void ATMainShotTower::TargetInRange()
{
	Super::TargetInRange();
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle,this,&ATMainShotTower::Fire,ShotTowerData.ShotRate, true);
}

void ATMainShotTower::NoTargetInRange()
{
	Super::NoTargetInRange();
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
}



