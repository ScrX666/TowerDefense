// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FTManState.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FTManState : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	FTManState();

	UPROPERTY(EditDefaultsOnly)
	USkeletalMesh* SkeletalMesh;
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth;
	UPROPERTY(EditDefaultsOnly)
	int32 Coins;
	UPROPERTY(EditDefaultsOnly)
	int32 Exp;
	UPROPERTY(EditDefaultsOnly)
	int32 Cost;
	UPROPERTY(EditDefaultsOnly)
	int32 Damage;
};
