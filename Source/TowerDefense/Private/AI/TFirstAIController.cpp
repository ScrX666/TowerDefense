// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TFirstAIController.h"

#include "AI/TSplineMapActor.h"

void ATFirstAIController::BeginPlay()
{
	Super::BeginPlay();
	if( ensureMsgf(BTEnemy,TEXT("BTEnemy is Null, please assign BehaviorTree")))
	{
		NextIndex = 0;
		RunBehaviorTree(BTEnemy);
	}
		
}

void ATFirstAIController::Tick(float DeltaSeconds)
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

void ATFirstAIController::Destroyed()
{
	Super::Destroyed();
	// 编辑器下编译也会调用，防止崩溃
	if( SplineMapActor)
	SplineMapActor->OnManDead();
}

FVector ATFirstAIController::GetNextPosition()
{
	NextIndex++;
	return SplineMapActor->GetTargetPos(NextIndex);
}
