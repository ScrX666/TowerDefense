// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TFirstAIController.generated.h"

class ATSplineMapActor;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATFirstAIController : public AAIController
{
	GENERATED_BODY()
public:
	ATSplineMapActor* SplineMapActor;
	FVector NextPosition;
	int NextIndex = 1;
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void Destroyed() override;
};
