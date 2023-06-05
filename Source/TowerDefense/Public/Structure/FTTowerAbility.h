// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FTManBuffer.h"
#include "Engine/DataTable.h"
#include "Enum/ETowerAbility.h"
#include "FTTowerAbility.generated.h"

/**
 * 塔满级后可以加点的能力
 */
USTRUCT(BlueprintType)
struct FTTowerAbility : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	ETowerAbility TowerAbilityType;

	UPROPERTY(EditDefaultsOnly)
	float DamageUp = 1.0f;
	UPROPERTY(EditDefaultsOnly)
	float AttackRangeUp = 1.0f;
	UPROPERTY(EditDefaultsOnly)
	int32 AdditiveParallel = 0;

	// 仅射击塔有效
	UPROPERTY(EditDefaultsOnly)
	float ShotRateUp = 1.0f;
	UPROPERTY(EditDefaultsOnly)
	float BulletSpeedUp = 1.0f;

	// Buff
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FTManBuffer AdditiveBuff;
};
