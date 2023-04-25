// Fill out your copyright notice in the Description page of Project Settings.


#include "Building/Tower/TMainTower.h"

#include "Character/TManBase.h"
#include "Components/SphereComponent.h"

ATMainTower::ATMainTower()
	:TargetMan(nullptr)
{
	AttackRangeComps = CreateDefaultSubobject<USceneComponent>(TEXT("AttackRangeComps"));
	AttackRangeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AttackRangeMesh"));
	AttackRangeSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AttackRangeSphere"));
	AttackRangeComps->SetupAttachment(RootComponent);
	AttackRangeMesh->SetupAttachment(AttackRangeComps);
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

void ATMainTower::Fire()
{
}

void ATMainTower::OnConstruct(ATMainAttachBase* AttachBase)
{
	Super::OnConstruct(AttachBase);

	if( AttachBase == nullptr)
	{
		UE_LOG(LogTemp,Log,TEXT("AttachBase Null"));
		return ;
	}
	else
	{
		UE_LOG(LogTemp,Log,TEXT("AttachBase Not Null"));
	}
	AttackRangeSphere->OnComponentBeginOverlap.AddDynamic(this, &ATMainTower::AttackRangeOverlap);
	AttackRangeSphere->OnComponentEndOverlap.AddDynamic(this, &ATMainTower::AttackRangeEndOverlap);
}
