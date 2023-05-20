// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "TBTServiceCheckAttackInRange.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTBTServiceCheckAttackInRange : public UBTService
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,Category = "AI")
	FBlackboardKeySelector AttackRangeKey;
	UPROPERTY(EditAnywhere,Category = "AI")
	float AttackRange;
public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
