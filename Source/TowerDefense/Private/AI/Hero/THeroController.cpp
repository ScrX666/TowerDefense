// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Hero/THeroController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Character/THero.h"

void ATHeroController::BeginPlay()
{
	Super::BeginPlay();
	if( ensureMsgf(BehaviorTree,TEXT("BTEnemy is Null, please assign BehaviorTree in ATHeroController")))
	{
		RunBehaviorTree(BehaviorTree);
	}
}

void ATHeroController::HeroMove(FVector MoveLoc)
{
	if( Blackboard)
	{
		if( SoloMan)
		{
			ATAIBaseController* AIC = Cast<ATAIBaseController>(SoloMan->GetController());
			if( AIC)
			{
				AIC->DisableSolo(nullptr);
			}
			DisableSolo(nullptr);
		}
		
		Blackboard->SetValueAsBool(TEXT("bHeroMove"),true);
		Blackboard->SetValueAsVector(TEXT("MoveToLocation"),MoveLoc);
	}
}

bool ATHeroController::CanBeSoloed()
{
	if( Blackboard)
	{
		bool bHeroMove = Blackboard->GetValueAsBool(TEXT("bHeroMove"));
		if( bHeroMove) return false;
	}
	return Super::CanBeSoloed();
}
