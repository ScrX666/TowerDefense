// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TBTTaskCalMoveLocation.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTBTTaskCalMoveLocation : public UBTTaskNode
{
	GENERATED_BODY()
private:
	FVector NextPos;
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
