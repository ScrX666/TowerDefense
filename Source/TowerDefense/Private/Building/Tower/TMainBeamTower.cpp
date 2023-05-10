// Fill out your copyright notice in the Description page of Project Settings.


#include "Building/Tower/TMainBeamTower.h"

#include "Component/ActorComp/TBeamTowerState.h"
#include "Component/ActorComp/Tower/TAttackHandleComponent.h"

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
	// if( LaserBeam)
	// {
	// 	LaserBeam->SetDamage(NewDamage);
	// }
	for( int i = 0; i < LaserBeams.Num(); i++)
	{
		if( IsValid(LaserBeams[i]))
		{
			LaserBeams[i]->SetDamage(NewDamage);
		}
	}
}

void ATMainBeamTower::SetLaserBeamsNum(const int32 NewCount)
{
	int32 NewNum = NewCount;
	int32 CurrentCount = LaserBeams.Num();
	//TODO: 用委托改写
	//TODO: 测试TArray中的UObject是否被自动GC
	if( NewNum > CurrentCount)
	{
		// 添加
		while(NewNum > CurrentCount)
		{
			LaserBeams.Add(nullptr);
			LaserBeamBeUsed.Add(false);
			NewNum--;
		}
	}
	else
	{
		// 删除
		while(NewNum < CurrentCount)
		{
			LaserBeams.RemoveAt(LaserBeams.Num() - 1);
			LaserBeamBeUsed.RemoveAt(LaserBeamBeUsed.Num() - 1);
			CurrentCount--;
		}
	}
}

int32 ATMainBeamTower::GetCostCoins()
{
	return BeamTowerStateComp->GetCostCoins();
}
/*
 * 与其说开火造成伤害，不如说是更新每个激光的状态
 */
void ATMainBeamTower::Fire()
{
	// if( TargetMan == nullptr)
	// 	return ;
	
	Super::Fire();
	
	const int32 ParallelAttackCount = AttackHandleComponent->GetParallelAttackCount();
	for(int i = 0; i < ParallelAttackCount; i++)
	{
		ATManBase* TargetMan = AttackHandleComponent->GetAttackTarget(i);

		auto Socket = BuildingMesh->GetSocketByName(TEXT("BulletSocket"));
		if( Socket == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Socket NULL"));
			return ;
		}
		if( !IsValid(LaserBeams[i]) && IsValid(BeamClass))
		{
			FActorSpawnParameters ActorSpawnParameters;
			ActorSpawnParameters.Owner = this;
		
			LaserBeams[i] = GetWorld()->SpawnActor<ATLaserBeam>(BeamClass,BuildingMesh->GetSocketTransform(TEXT("BulletSocket")),ActorSpawnParameters);
		}
		LaserBeams[i]->Init(TargetMan,BeamTowerStateComp->CurrentDamage);
	}
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
	// if( LaserBeam)
	// {
	// 	LaserBeam->Destroy();
	// 	LaserBeam = nullptr;
	// }
	// 本类Fire的实现 与其说开火造成伤害，不如说是更新每个激光的状态
	UE_LOG(LogTemp,Log,TEXT("NoTargetInRange BeamTower"));
	Fire();
}
void ATMainBeamTower::GetExp(int Exp)
{
	// Super::GetExp();
	BeamTowerStateComp->GetExp(Exp);
}
