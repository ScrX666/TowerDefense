// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TBTTaskAttack.h"

#include "AIController.h"
#include "Character/TManBase.h"

EBTNodeResult::Type UTBTTaskAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ATManBase* ManBase = Cast<ATManBase>(OwnerComp.GetAIOwner()->GetPawn());
	if( ManBase)
	{
		ManBase->Attack();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
