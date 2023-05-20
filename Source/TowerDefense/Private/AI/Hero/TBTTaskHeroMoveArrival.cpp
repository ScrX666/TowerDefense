// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Hero/TBTTaskHeroMoveArrival.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/THero.h"

EBTNodeResult::Type UTBTTaskHeroMoveArrival::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackBoard = OwnerComp.GetAIOwner()->GetBlackboardComponent();
	if( BlackBoard)
	{
		BlackBoard->SetValueAsBool(TEXT("bHeroMove"),false);
		ATHero* Hero = Cast<ATHero>(OwnerComp.GetAIOwner()->GetPawn());
		if( Hero)
		{
			Hero->ManualPerceptionUpdated();
		}
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
