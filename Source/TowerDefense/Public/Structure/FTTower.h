// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FTTower.generated.h"

/*
 * 塔的信息 弃用
 */
USTRUCT(BlueprintType)
struct FTTower : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	
	UPROPERTY(EditDefaultsOnly)
	float AttackRange = 100.0f;
};
