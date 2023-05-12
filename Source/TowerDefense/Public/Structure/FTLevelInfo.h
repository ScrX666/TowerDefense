// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FTLevelInfo.generated.h"

class ATMainTower;
/**
 * 
 */
USTRUCT(BlueprintType)
struct TOWERDEFENSE_API FTLevelInfo : public FTableRowBase
{
 GENERATED_USTRUCT_BODY()
 UPROPERTY(EditDefaultsOnly)
 TSoftObjectPtr<UWorld> Level;
 UPROPERTY(EditDefaultsOnly)
 TArray<TSubclassOf<ATMainTower>> WinTowers;
};
