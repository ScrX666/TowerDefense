// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TBTTaskCalMoveLocation.h"

#include "AIController.h"
#include "AI/TAIBaseController.h"
#include "AI/Enemy/TEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UTBTTaskCalMoveLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ATEnemyAIController* EnemyAIController = Cast<ATEnemyAIController>(OwnerComp.GetAIOwner());
	if(EnemyAIController)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("MoveToLocation"),EnemyAIController->GetNextPosition());
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
