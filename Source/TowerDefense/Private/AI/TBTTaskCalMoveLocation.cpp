// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TBTTaskCalMoveLocation.h"

#include "AIController.h"
#include "AI/TFirstAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UTBTTaskCalMoveLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ATFirstAIController* FAI = Cast<ATFirstAIController>(OwnerComp.GetAIOwner());
	if(FAI)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("MoveToLocation"),FAI->GetNextPosition());
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
