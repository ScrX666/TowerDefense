// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ActorComp/TShotTowerState.h"

#include "Structure/FTTowerAbility.h"
#include "Building/Tower/TMainShotTower.h"
#include "Building/Tower/TMainTower.h"
#include "Component/ActorComp/Tower/TAttackHandleComponent.h"
#include "GamePlay/TDataTableManager.h"

// Sets default values for this component's properties
UTShotTowerState::UTShotTowerState()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTShotTowerState::BeginPlay()
{
	Super::BeginPlay();

	Tower = Cast<ATMainTower>(GetOwner());
	
	OnLevelUp.AddDynamic(this, &UTShotTowerState::UpdateLevel);
	OnLevelUp.AddDynamic(this, &UTShotTowerState::UpdateDamage);
	OnLevelUp.AddDynamic(this, &UTShotTowerState::UpdateAttackRange);
	OnLevelUp.AddDynamic(this, &UTShotTowerState::UpdateBulletSpeed);
	OnLevelUp.AddDynamic(this, &UTShotTowerState::UpdateShotRate);
	// ...
	// 防止 CurrentExp = -ShotTowerData.LevelUpExp; 的BUG
	CurrentExp = ShotTowerData.LevelUpExp;
	UpdateParallelAttackCount(ShotTowerData.ParallelAttackCount);
	OnLevelUp.Broadcast(0);
}

void UTShotTowerState::UpdateLevel(int32 NewLevel)
{
	CurrentExp -= ShotTowerData.LevelUpExp;
	CurrentLevel = NewLevel;
}

void UTShotTowerState::UpdateDamage(const int32 NewLevel)
{
	float AddDamage = 0.0f;
	for( int i = 0; i < NewLevel; i++)
	{
		AddDamage += ShotTowerData.DamageUpGrade * ShotTowerData.BaseDamage;
	}
	CurrentDamage = ShotTowerData.BaseDamage + AddDamage;
}

void UTShotTowerState::UpdateAttackRange(const int32 NewLevel)
{
	float AddAttackRange = 0.0f;
	for( int i = 0; i < NewLevel; i++)
	{
		AddAttackRange += ShotTowerData.AttackRangeUpGrade * ShotTowerData.AttackRange;
	}
	CurrentAttackRange = ShotTowerData.AttackRange + AddAttackRange;
	if( Tower)
	{
		Tower->UpdateAttackRange(CurrentAttackRange);
	}
}

void UTShotTowerState::UpdateBulletSpeed(const int32 NewLevel)
{
	float AddBulletSpeed = 0.0f;
	for( int i = 0; i < NewLevel; i++)
	{
		AddBulletSpeed += ShotTowerData.BulletSpeedUpGrade * ShotTowerData.BulletSpeed;
	}
	BulletSpeed = ShotTowerData.BulletSpeed + AddBulletSpeed;
}

void UTShotTowerState::UpdateShotRate(const int32 NewLevel)
{
	float AddShotRate = 0.0f;
	for( int i = 0; i < NewLevel; i++)
	{
		AddShotRate += ShotTowerData.ShotRateUpGrade * ShotTowerData.ShotRate;
	}
	ShotRate = ShotTowerData.ShotRate - AddShotRate;
	if( ShotRate <= 0.1f) ShotRate = 0.1f;
	if( Tower && Tower->IsA<ATMainShotTower>())
	{
		Cast<ATMainShotTower>(Tower)->UpdateShotRate(ShotRate);
	}
}

void UTShotTowerState::UpdateParallelAttackCount(const int32 NewCount)
{
	ParallelAttackCount = NewCount;
	if( Tower)
	{
		Tower->AttackHandleComponent->SetParallelAttackCount(ParallelAttackCount);
	}
}


// Called every frame
void UTShotTowerState::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
/*
 * 初始化
 */
void UTShotTowerState::Init(const FName Name)
{
	UE_LOG(LogTemp,Log,TEXT("TMainShotTower Init"));
	ShotTowerData = TDataTableManager::GetInstance()->GetShotTowerData(Name);
	UpdateAttackRange(0);
}
/*
 * 获取Exp
 */
void UTShotTowerState::GetExp(const int Exp)
{
	if( CurrentLevel >= ShotTowerData.MaxLevel) return ;
	
	CurrentExp += Exp;
	if( CurrentExp >= ShotTowerData.LevelUpExp)
	{
		OnLevelUp.Broadcast(CurrentLevel + 1);
		if( CurrentLevel == ShotTowerData.MaxLevel)
		{
			// 满级后 解绑事件
			OnLevelUp.Clear();
			CurrentExp = ShotTowerData.LevelUpExp;
			OnGetExp.Broadcast(this);
			OnGetExp.Clear();
		}
	}
	OnGetExp.Broadcast(this);
}

TSubclassOf<ATMainBullet> UTShotTowerState::GetBulletClass() const
{
	return ShotTowerData.Bullet;
}

USoundBase* UTShotTowerState::GetSoundClass() const
{
	return ShotTowerData.ShotSound;
}

int32 UTShotTowerState::GetLevelUpExp() const
{
	return ShotTowerData.LevelUpExp;
}

int32 UTShotTowerState::GetCostCoins() const
{
	return ShotTowerData.CostCoins;
}

const TArray<FTManBuffer>& UTShotTowerState::GetApplyBuffers() const
{
	return ShotTowerData.Buffers;
}

void UTShotTowerState::ApplyAbility(const FTTowerAbility& TowerAbility)
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
		ShotRate *= TowerAbility.ShotRateUp;
		Tower->UpdateAttackRange(CurrentAttackRange);
		break;
	case ETowerAbility::E_BulletSpeed:
		BulletSpeed *= TowerAbility.BulletSpeedUp;
		break;
	case ETowerAbility::E_Buff:
		{
			Tower->AddBuffer(TowerAbility.AdditiveBuff);
		}
		break;
	default: ;
	}
}

const TArray<FTTowerAbility>& UTShotTowerState::GetAllAbility() const
{
	return ShotTowerData.TowerAbilities;
}

int32 UTShotTowerState::GetMaxLevel() const
{
	return ShotTowerData.MaxLevel;
}

