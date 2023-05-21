// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/TBaseSkill.h"
#include "TBaseLocationSkill.generated.h"

/**
 * 需要释放技能的Skill
 */
UCLASS(BlueprintType,Abstract)
class TOWERDEFENSE_API UTBaseLocationSkill : public UTBaseSkill
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere)
	FVector SpawnLocation;
public:
	virtual void Execute(UWorld* World) override;
};
