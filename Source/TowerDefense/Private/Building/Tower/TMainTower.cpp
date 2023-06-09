// Fill out your copyright notice in the Description page of Project Settings.


#include "Building/Tower/TMainTower.h"

#include "Character/TManBase.h"
#include "Component/ActorComp/Tower/TAttackHandleComponent.h"
#include "Components/SphereComponent.h"
#include "Structure/FTManBuffer.h"

ATMainTower::ATMainTower()
{
	AttackRangeComps = CreateDefaultSubobject<USceneComponent>(TEXT("AttackRangeComps"));
	AttackRangeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AttackRangeMesh"));
	AttackRangeSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AttackRangeSphere"));
	AttackRangeComps->SetupAttachment(RootComponent);
	AttackRangeMesh->SetupAttachment(AttackRangeComps);
	AttackRangeMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackRangeSphere->SetupAttachment(AttackRangeComps);
	AttackRangeSphere->SetGenerateOverlapEvents(true);

	AttackHandleComponent = CreateDefaultSubobject<UTAttackHandleComponent>(TEXT("AttackHandleComp"));
	
	Name = FName(GetClass()->GetFName().ToString());
}

void ATMainTower::AttackRangeOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if( OtherActor != nullptr)
	{
		const auto Man = Cast<ATManBase>(OtherActor);
		AttackHandleComponent->AttackTargetIn(Man);
	}
}

void ATMainTower::AttackRangeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if( OtherActor != nullptr)
	{
		const auto Man = Cast<ATManBase>(OtherActor);
		AttackHandleComponent->AttackTargetOut(Man);
	}
}

void ATMainTower::UpdateAttackRange(const float NewRange)
{
	AttackRange = NewRange;
	AttackRangeSphere->SetSphereRadius(NewRange);
	AttackRangeMesh->SetWorldScale3D(FVector(AttackRange / 50.0f));
}


#pragma region 留给子类实现
void ATMainTower::TargetInRange()
{
}

void ATMainTower::NoTargetInRange()
{
}

void ATMainTower::GetExp(int Exp)
{
}
UTTowerStateComponent* ATMainTower::GetStateComp() const
{
	return nullptr;
}
#pragma endregion

void ATMainTower::AddBuffer(const FTManBuffer& Buffer)
{
	ApplyBuffers.Add(Buffer);
}

void ATMainTower::BeginPlay()
{
	Super::BeginPlay();
	// AttackRangeSphere->OnComponentBeginOverlap.AddDynamic(this, &ATMainTower::AttackRangeOverlap);
	// AttackRangeSphere->OnComponentEndOverlap.AddDynamic(this, &ATMainTower::AttackRangeEndOverlap);
	UE_LOG(LogTemp,Log,TEXT("Class Name %s"),*Name.ToString());
}

void ATMainTower::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	// 根据Name加载信息
	// TowerData = TDataTableManager::GetInstance()->GetTowerData(Name);
	// AttackRangeSphere->SetSphereRadius(TowerData.AttackRange);
	// UE_LOG(LogTemp,Log,TEXT("OnConstruction MainTower AttackRange %f"), TowerData.AttackRange);
}

void ATMainTower::Fire()
{
}

void ATMainTower::OnSelected(bool bSelected)
{
	if( bSelected)
	{
		if( Materials.Contains(TEXT("Range")))
		{
			AttackRangeMesh->SetMaterial(0,Materials[TEXT("Range")]);
		}
		
		AttackRangeMesh->SetVisibility(true);
		// 动态设置攻击范围显示
		// AttackRangeMesh->SetWorldScale3D(FVector(AttackRange / 200.0f));
	}
	else
	{
		AttackRangeMesh->SetVisibility(false);
	}
}

void ATMainTower::OnConstruct(ATMainAttachBase* AttachBase)
{
	Super::OnConstruct(AttachBase);
	
	if( AttachBase == nullptr)
	{
		UE_LOG(LogTemp,Log,TEXT("AttachBase Null"));
		AttackRangeMesh->SetVisibility(true);
		// 动态设置攻击范围显示
		//AttackRangeMesh->SetWorldScale3D(FVector(AttackRange / 200.0f,AttackRange / 200.0f,1));
		UpdateAttackRange(AttackRange);
		return ;
	}
	else
	{
		UE_LOG(LogTemp,Log,TEXT("AttachBase Not Null"));

		AttackRangeMesh->SetVisibility(false);
		AttackRangeSphere->OnComponentBeginOverlap.AddDynamic(this, &ATMainTower::AttackRangeOverlap);
		AttackRangeSphere->OnComponentEndOverlap.AddDynamic(this, &ATMainTower::AttackRangeEndOverlap);

		//生成时 函数还没有绑定，TargetMan 没有指定，手动触发一次
		AttackRangeSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		AttackRangeSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		return;
	}
}
