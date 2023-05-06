// Fill out your copyright notice in the Description page of Project Settings.


#include "Building/Tower/TMainShotTower.h"

#include "Component/ActorComp/TShotTowerState.h"
#include "Engine/StaticMeshSocket.h"
#include "GamePlay/TDataTableManager.h"
#include "Kismet/GameplayStatics.h"
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
	if( TargetMan)
	{
		GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(FireTimerHandle,this,&ATMainShotTower::Fire,ShotRate, true);
	}
}

int32 ATMainShotTower::GetCostCoins()
{
	return ShotTowerStateComp->GetCostCoins();
}

void ATMainShotTower::Fire()
{
	UE_LOG(LogTemp,Log,TEXT("Fire"));
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
	if( ShotTowerStateComp->GetSoundClass() != nullptr)
	{
		UGameplayStatics::PlaySound2D(this,ShotTowerStateComp->GetSoundClass());
	}

	// 生成子弹
	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.Owner = this;
	
	auto Bullet = GetWorld()->SpawnActor<ATMainBullet>(BulletClass,BuildingMesh->GetSocketTransform(TEXT("BulletSocket")),ActorSpawnParameters);
	if( Bullet != nullptr)
	{
		Bullet->Init(TargetMan,ShotTowerStateComp->BulletSpeed,ShotTowerStateComp->CurrentDamage);
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
	UE_LOG(LogTemp,Log,TEXT("TargetInRange ShotTowerStateComp->ShotRate %f"),ShotTowerStateComp->ShotRate);
	Super::TargetInRange();
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle,this,&ATMainShotTower::Fire,ShotTowerStateComp->ShotRate, true);
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



