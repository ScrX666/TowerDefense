// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AI/TAIBaseController.h"
#include "THeroController.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATHeroController : public ATAIBaseController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	void HeroMove(FVector MoveLoc);
	virtual bool CanBeSoloed() const override;
};
