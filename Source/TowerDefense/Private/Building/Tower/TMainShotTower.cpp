// Fill out your copyright notice in the Description page of Project Settings.


#include "Building/Tower/TMainShotTower.h"

#include "Engine/StaticMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile/TMainBullet.h"

ATMainShotTower::ATMainShotTower()
{
}

void ATMainShotTower::OnConstruct(ATMainAttachBase* AttachBase)
{
	Super::OnConstruct(AttachBase);

	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle,this,&ATMainShotTower::Fire,2.0f, true);
}

void ATMainShotTower::BeginPlay()
{
	Super::BeginPlay();
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
	auto Bullet = GetWorld()->SpawnActor<ATMainBullet>(BulletClass);


	Bullet->SetActorLocationAndRotation(Socket->RelativeLocation + BuildingMesh->GetComponentLocation(),FRotator::ZeroRotator);
	Bullet->Init(TargetMan);
}

void ATMainShotTower::OnDestory()
{
	Super::OnDestory();
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
}



