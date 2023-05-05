// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
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
	float ShotRate = 2.0f;
	UPROPERTY(EditDefaultsOnly)
	float ShotRateUpGrade = 1.5f;
	
	UPROPERTY(EditDefaultsOnly)
	USoundBase* ShotSound;
	
	UPROPERTY(EditDefaultsOnly)
	float AttackRange = 100.0f;
	UPROPERTY(EditDefaultsOnly)
	float AttackRangeUpGrade = 1.5f;
	
	UPROPERTY(EditDefaultsOnly)
	float BaseDamage = 10.0f;
	UPROPERTY(EditDefaultsOnly)
	float DamageUpGrade = 1.5f;

	UPROPERTY(EditDefaultsOnly)
	float BulletSpeed = 200.0f;
	UPROPERTY(EditDefaultsOnly)
	float BulletSpeedUpGrade = 1.5f;
	
	UPROPERTY(EditDefaultsOnly)
	int32 LevelUpExp = 100;
};
