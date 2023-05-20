// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/TAIBaseController.h"
#include "TEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATEnemyAIController : public ATAIBaseController
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere)
	ATSplineMapActor* SplineMapActor;
	
	FVector NextPosition;
	int NextIndex = 0;
public:
	FVector GetNextPosition();
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
};
