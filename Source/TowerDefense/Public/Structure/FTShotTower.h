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
	float ShotRate = 1.0f;
};
