// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TBTTaskCalMoveLocation.h"

#include "AIController.h"
#include "AI/TAIBaseController.h"
#include "AI/Enemy/TEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UTBTTaskCalMoveLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ATEnemyAIController* EnemyAIController = Cast<ATEnemyAIController>(OwnerComp.GetAIOwner());
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if(EnemyAIController && BlackboardComponent)
	{
		if(BlackboardComponent->GetValueAsBool(TEXT("bHasAttacked")))
		{
			// 攻击后 恢复沿样条线走
			BlackboardComponent->SetValueAsVector(TEXT("MoveToLocation"),EnemyAIController->GetClosetPosition());
			BlackboardComponent->SetValueAsBool(TEXT("bHasAttacked"), false);
			return EBTNodeResult::Succeeded;
		}
		else
		{
			// 未攻击过按照路线走
			BlackboardComponent->SetValueAsVector(TEXT("MoveToLocation"),EnemyAIController->GetNextPosition());
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
