// Fill out your copyright notice in the Description page of Project Settings.


#include "Building/Tower/TMainTower.h"

#include "Character/TManBase.h"
#include "Components/SphereComponent.h"
#include "GamePlay/TDataTableManager.h"

ATMainTower::ATMainTower()
	:TargetMan(nullptr)
{
	AttackRangeComps = CreateDefaultSubobject<USceneComponent>(TEXT("AttackRangeComps"));
	AttackRangeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AttackRangeMesh"));
	AttackRangeSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AttackRangeSphere"));
	AttackRangeComps->SetupAttachment(RootComponent);
	AttackRangeMesh->SetupAttachment(AttackRangeComps);
	AttackRangeMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackRangeSphere->SetupAttachment(AttackRangeComps);
	AttackRangeSphere->SetGenerateOverlapEvents(true);

}

void ATMainTower::AttackRangeOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if( OtherActor != nullptr)
	{
		auto OthMan = Cast<ATManBase>(OtherActor);
		if( OthMan != nullptr && !IsValid(TargetMan))
		{
			TargetMan = OthMan;
		}
	}
}

void ATMainTower::AttackRangeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if( OtherActor->IsA<ATManBase>())
	{
		TArray<AActor*> ManBases;
		GetOverlappingActors(ManBases, ATManBase::StaticClass());
		if( ManBases.Num() == 0) TargetMan = nullptr;
		else TargetMan = Cast<ATManBase>(ManBases[0]);
	}
}

void ATMainTower::BeginPlay()
{
	Super::BeginPlay();
	// AttackRangeSphere->OnComponentBeginOverlap.AddDynamic(this, &ATMainTower::AttackRangeOverlap);
	// AttackRangeSphere->OnComponentEndOverlap.AddDynamic(this, &ATMainTower::AttackRangeEndOverlap);
}

void ATMainTower::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	// 根据Name加载信息
	TowerData = TDataTableManager::GetInstance()->GetTowerData(Name);
	AttackRangeSphere->SetSphereRadius(TowerData.AttackRange);
	UE_LOG(LogTemp,Log,TEXT("OnConstruction MainTower AttackRange %f"), TowerData.AttackRange);
}

void ATMainTower::Fire()
{
}

void ATMainTower::OnConstruct(ATMainAttachBase* AttachBase)
{
	Super::OnConstruct(AttachBase);

	
	
	if( AttachBase == nullptr)
	{
		UE_LOG(LogTemp,Log,TEXT("AttachBase Null"));
		AttackRangeMesh->SetVisibility(true);
		// 动态设置攻击范围显示
		AttackRangeMesh->SetWorldScale3D(FVector(TowerData.AttackRange / 200.0f));
		return ;
	}
	else
	{
		UE_LOG(LogTemp,Log,TEXT("AttachBase Not Null"));
	}
	AttackRangeMesh->SetVisibility(false);
	AttackRangeSphere->OnComponentBeginOverlap.AddDynamic(this, &ATMainTower::AttackRangeOverlap);
	AttackRangeSphere->OnComponentEndOverlap.AddDynamic(this, &ATMainTower::AttackRangeEndOverlap);
}
