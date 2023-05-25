// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FTTowerAbility.h"
#include "Engine/DataTable.h"
#include "Structure/FTManBuffer.h"
#include "FTShotTower.generated.h"

class ATMainBullet;

/*
 * 射击塔的信息
 */
USTRUCT(BlueprintType)
struct FTShotTower : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATMainBullet> Bullet;
	UPROPERTY(EditDefaultsOnly)
	TArray<FTManBuffer> Buffers;
	
	UPROPERTY(EditDefaultsOnly)
	float ShotRate = 2.0f;
	UPROPERTY(EditDefaultsOnly)
	float ShotRateUpGrade = 0.5f;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<USoundBase*> ShotSounds;
	
	UPROPERTY(EditDefaultsOnly)
	float AttackRange = 100.0f;
	UPROPERTY(EditDefaultsOnly)
	float AttackRangeUpGrade = 0.5f;
	
	UPROPERTY(EditDefaultsOnly)
	float BaseDamage = 10.0f;
	UPROPERTY(EditDefaultsOnly)
	float DamageUpGrade = 0.5f;

	UPROPERTY(EditDefaultsOnly)
	float BulletSpeed = 200.0f;
	UPROPERTY(EditDefaultsOnly)
	float BulletSpeedUpGrade = 0.5f;
	
	UPROPERTY(EditDefaultsOnly)
	int32 LevelUpExp = 100;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	int32 CostCoins = 100;
	// 同时攻击敌人数量
	UPROPERTY(EditDefaultsOnly)
	int32 ParallelAttackCount = 1;

	UPROPERTY(EditDefaultsOnly)
	int32 MaxLevel = 3;

	// 塔满级后可以加点的能力
	UPROPERTY(EditDefaultsOnly)
	TArray<FTTowerAbility> TowerAbilities;
};
