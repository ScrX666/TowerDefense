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
	TSubclassOf<ATLaserBeam> Bullet;
	UPROPERTY(EditDefaultsOnly)
	float Damage = 2.0f;
	// UPROPERTY(EditDefaultsOnly)
	// USoundBase* ShotSound;
};
