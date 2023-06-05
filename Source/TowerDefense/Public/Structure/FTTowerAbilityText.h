// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FTTowerAbilityText.generated.h"

/**
 * 塔满级后可以加点的能力的描述
 */
USTRUCT(BlueprintType)
struct FTTowerAbilityText : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText Description;
};
