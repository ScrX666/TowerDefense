// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Skill/TBaseSkill.h"
#include "FTSKillButtonInfo.generated.h"

class UImage;
/**
 * 技能图标信息
 */
USTRUCT(BlueprintType)
struct TOWERDEFENSE_API FTSKillButtonInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<UTBaseSkill> Skill;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UTexture2D* Icon;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText Description;
};