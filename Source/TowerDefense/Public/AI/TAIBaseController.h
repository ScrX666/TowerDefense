// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TAIBaseController.generated.h"

class ATSplineMapActor;
class ATManBase;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATAIBaseController : public AAIController
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree* BehaviorTree;
protected:
	UPROPERTY()
	ATManBase* SoloMan;
	UPROPERTY()
	bool bIsSoloed;
protected:
	UPROPERTY()
	ATManBase* OwnMan;
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	virtual bool CanBeSoloed() const;
	UFUNCTION()
	void DisableSolo(AActor* InstigatorActor);
	UFUNCTION()
	void PerceptionUpdated(AActor* InstigatorActor);
	void SetSoloTarget(ATManBase* TargetMan);
	ATManBase* GetAttackMan() const; 
};
