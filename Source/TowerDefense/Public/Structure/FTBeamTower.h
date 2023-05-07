// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Projectile/TLaserBeam.h"
#include "FTBeamTower.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FTBeamTower : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	USoundBase* ShotSound;
	UPROPERTY(EditDefaultsOnly)
	float BaseDamage = 2.0f;
	UPROPERTY(EditDefaultsOnly)
	float DamageUpGrade = 0.5f;
	
	// UPROPERTY(EditDefaultsOnly)
	// USoundBase* ShotSound;
	UPROPERTY(EditDefaultsOnly)
	float AttackRange = 100.0f;
	UPROPERTY(EditDefaultsOnly)
	float AttackRangeUpGrade = 0.5f;

	UPROPERTY(EditDefaultsOnly)
	int32 LevelUpExp = 100;
	UPROPERTY(EditDefaultsOnly)
	int32 CostCoins = 100;
	UPROPERTY(EditDefaultsOnly)
	int32 ParallelAttackCount = 1;
};
