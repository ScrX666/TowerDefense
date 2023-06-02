// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemy/TEnemyAIController.h"

#include "AI/TSplineMapActor.h"




void ATEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	NextIndex = 0;
}
FVector ATEnemyAIController::GetNextPosition()
{
	NextIndex++;
	if(SplineMapActor)
		return SplineMapActor->GetTargetPos(NextIndex);
	else
		return FVector(0.0f);
}

FVector ATEnemyAIController::GetClosetPosition()
{
	NextIndex--;
	return SplineMapActor->GetClosestPoint(GetPawn()->GetActorLocation(),NextIndex);
}

void ATEnemyAIController::Destroyed()
{
	Super::Destroyed();
	// 编辑器下编译也会调用，防止崩溃
	if( SplineMapActor)
		SplineMapActor->OnManDead();
}
