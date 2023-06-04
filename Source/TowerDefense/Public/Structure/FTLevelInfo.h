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
 UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
 FName LevelName;
 UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
 TArray<TSubclassOf<ATMainTower>> WinTowers;
 UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
 int32 InitCoins = 100;
 UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
 USoundBase* AmbientSound;
 UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
 USoundBase* BackgroundMusic;
 UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
 UDataTable* BeginDialogTable;
 UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
 UDataTable* EndDialogTable;
 UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
 UTexture2D* ChangeLevelTexture;
 /**
  * 每一关塔的攻击范围修正
  */
 UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
 float TowerAttackRangeAmend = 1.0f;
};
