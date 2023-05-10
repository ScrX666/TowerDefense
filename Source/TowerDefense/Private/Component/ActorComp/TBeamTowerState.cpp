// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ActorComp/TBeamTowerState.h"

#include "Structure/FTTowerAbility.h"
#include "Building/Tower/TMainBeamTower.h"
#include "Building/Tower/TMainTower.h"
#include "Component/ActorComp/Tower/TAttackHandleComponent.h"
#include "GamePlay/TDataTableManager.h"

// Sets default values for this component's properties
UTBeamTowerState::UTBeamTowerState()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}



// Called when the game starts
void UTBeamTowerState::BeginPlay()
{
	Super::BeginPlay();
	
	Tower = Cast<ATMainTower>(GetOwner());
	
	OnLevelUp.AddDynamic(this, &UTBeamTowerState::UpdateLevel);
	OnLevelUp.AddDynamic(this, &UTBeamTowerState::UpdateDamage);
	OnLevelUp.AddDynamic(this, &UTBeamTowerState::UpdateAttackRange);
	
	// 防止 CurrentExp = -ShotTowerData.LevelUpExp; 的BUG
	CurrentExp = BeamTowerData.LevelUpExp;
	UpdateParallelAttackCount(BeamTowerData.ParallelAttackCount);
	OnLevelUp.Broadcast(0);
}

void UTBeamTowerState::UpdateLevel(int32 NewLevel)
{
	CurrentExp -= BeamTowerData.LevelUpExp;
	CurrentLevel = NewLevel;
}

void UTBeamTowerState::UpdateDamage(const int32 NewLevel)
{
	float AddDamage = 0.0f;
	for( int i = 0; i < NewLevel; i++)
	{
		AddDamage += BeamTowerData.DamageUpGrade * BeamTowerData.BaseDamage;
	}
	CurrentDamage = BeamTowerData.BaseDamage + AddDamage;
}

void UTBeamTowerState::UpdateAttackRange(const int32 NewLevel)
{
	float AddAttackRange = 0.0f;
	for( int i = 0; i < NewLevel; i++)
	{
		AddAttackRange += BeamTowerData.AttackRangeUpGrade * BeamTowerData.AttackRange;
	}
	CurrentAttackRange = BeamTowerData.AttackRange + AddAttackRange;
	if( Tower)
	{
		Tower->UpdateAttackRange(CurrentAttackRange);
	}
}

void UTBeamTowerState::UpdateParallelAttackCount(const int32 NewCount)
{
	ParallelAttackCount = NewCount;
	if( Tower && Tower->IsA<ATMainBeamTower>())
	{
		Tower->AttackHandleComponent->SetParallelAttackCount(ParallelAttackCount);
		Cast<ATMainBeamTower>(Tower)->SetLaserBeamsNum(ParallelAttackCount);
	}
}


// Called every frame
void UTBeamTowerState::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
/*
 * 初始化
 */
void UTBeamTowerState::Init(const FName Name)
{
	UE_LOG(LogTemp,Log,TEXT("TMainShotTower Init"));
	BeamTowerData = TDataTableManager::GetInstance()->GetBeamTowerData(Name);
	UpdateAttackRange(0);
}
/*
 * 获取Exp
 */
void UTBeamTowerState::GetExp(const int Exp)
{
	CurrentExp += Exp;
	if( CurrentExp >= BeamTowerData.LevelUpExp)
	{
		OnLevelUp.Broadcast(CurrentLevel + 1);
	}
	OnGetExp.Broadcast(this);
}

USoundBase* UTBeamTowerState::GetSoundClass() const
{
	return BeamTowerData.ShotSound;
}

int32 UTBeamTowerState::GetLevelUpExp() const
{
	return BeamTowerData.LevelUpExp;
}

int32 UTBeamTowerState::GetCostCoins() const
{
	return BeamTowerData.CostCoins;
}

const TArray<FTManBuffer>& UTBeamTowerState::GetApplyBuffers() const
{
	return BeamTowerData.Buffers;
}

void UTBeamTowerState::ApplyAbility(const FTTowerAbility& TowerAbility)
{
	// Super::ApplyAbility(TowerAbility);
	switch (TowerAbility.TowerAbilityType)
	{
	case ETowerAbility::E_Damage:
		CurrentDamage *= TowerAbility.DamageUp;
		break;
	case ETowerAbility::E_AttackRange:
		CurrentAttackRange *= TowerAbility.AttackRangeUp;
		Tower->UpdateAttackRange(CurrentAttackRange);
		break;
	case ETowerAbility::E_ParallelAttack:
		ParallelAttackCount += TowerAbility.AdditiveParallel;
		Tower->AttackHandleComponent->SetParallelAttackCount(ParallelAttackCount);
		break;
	case ETowerAbility::E_ShotRate:
		UE_LOG(LogTemp,Warning,TEXT("ShotRate Can not apply to BeamTower"));
		break;
	case ETowerAbility::E_BulletSpeed:
		UE_LOG(LogTemp,Warning,TEXT("BulletSpeed Can not apply to BeamTower"));
		break;
	case ETowerAbility::E_Buff:
		{
			Tower->AddBuffer(TowerAbility.AdditiveBuff);
		}
		break;
	default: ;
	}
}

const TArray<FTTowerAbility>& UTBeamTowerState::GetAllAbility() const
{
	return BeamTowerData.TowerAbilities;
}

int32 UTBeamTowerState::GetMaxLevel() const
{
	return BeamTowerData.MaxLevel;
}

