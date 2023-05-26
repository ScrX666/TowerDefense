// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TAIBaseController.h"

#include "AI/TSplineMapActor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Component/ActorComp/TManStateAndBuffer.h"

void ATAIBaseController::BeginPlay()
{
	Super::BeginPlay();
	if( ensureMsgf(BehaviorTree,TEXT("BTEnemy is Null, please assign BehaviorTree")))
	{
		RunBehaviorTree(BehaviorTree);
	}
}

void ATAIBaseController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
#pragma region 原AI移动逻辑
	// FVector CurPos =  this->GetPawn()->GetTargetLocation();
	// CurPos.Z = NextPosition.Z;
	// // float size = (NextPosition - CurPos).Size();
	// // UE_LOG(LogTemp,Log,TEXT("%f"),size);
	// // UE_LOG(LogTemp,Log,TEXT("%s"),*NextPosition.ToString());
	// // UE_LOG(LogTemp,Log,TEXT("%s"),*CurPos.ToString());
	// if( (NextPosition - CurPos).Size() < 1)
	// {
	// 	NextIndex++;
	// 	SplineMapActor->MoveTo(this, NextIndex, NextPosition);
	// }
#pragma endregion
}

bool ATAIBaseController::CanBeSoloed()
{
	if( !OwnMan) OwnMan = Cast<ATManBase>(GetPawn());
	if( OwnMan->ManStateAndBuffer->CurrentHealth <= 0) return false;
	
	return !bIsSoloed;
}

void ATAIBaseController::DisableSolo(AActor* InstigatorActor)
{
	bIsSoloed = false;
	if( SoloMan)
	{
		SoloMan->ManStateAndBuffer->OnDead.RemoveDynamic(this,&ATAIBaseController::PerceptionUpdated);
		SoloMan->ManStateAndBuffer->OnDead.RemoveDynamic(this,&ATAIBaseController::DisableSolo);
	}
	if( Blackboard)
		Blackboard->SetValueAsObject(TEXT("TargetActor"),nullptr);
	SoloMan = nullptr;
}
/*
 * 对方死亡后，手动更新攻击对象，绑定到死亡的委托上
 */
void ATAIBaseController::PerceptionUpdated(AActor* InstigatorActor)
{
	if( !OwnMan)
		OwnMan = Cast<ATManBase>(GetPawn());
	if( OwnMan)
		OwnMan->ManualPerceptionUpdated();
}

void ATAIBaseController::SetSoloTarget(ATManBase* TargetMan)
{
	bIsSoloed = true;
	SoloMan = TargetMan;
	if( Blackboard)
		Blackboard->SetValueAsObject(TEXT("TargetActor"),TargetMan);
	TargetMan->ManStateAndBuffer->OnDead.AddDynamic(this,&ATAIBaseController::DisableSolo);
	TargetMan->ManStateAndBuffer->OnDead.AddDynamic(this,&ATAIBaseController::PerceptionUpdated);
}

ATManBase* ATAIBaseController::GetAttackMan() const
{
	return SoloMan;
}
