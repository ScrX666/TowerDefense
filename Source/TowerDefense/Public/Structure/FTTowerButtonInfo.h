// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Building/Tower/TMainTower.h"
#include "Engine/DataTable.h"
#include "FTTowerButtonInfo.generated.h"

class UImage;
/**
 * 
 */
USTRUCT(BlueprintType)
struct TOWERDEFENSE_API FTTowerButtonInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<ATMainTower> Tower;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UTexture2D* Icon;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText Description;
};
