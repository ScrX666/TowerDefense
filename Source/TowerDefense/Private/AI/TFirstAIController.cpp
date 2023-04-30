// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TFirstAIController.h"

#include "AI/TSplineMapActor.h"

void ATFirstAIController::BeginPlay()
{
	Super::BeginPlay();
	// SplineMapActor->MoveTo()
}

void ATFirstAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FVector CurPos =  this->GetPawn()->GetTargetLocation();
	CurPos.Z = NextPosition.Z;
	// float size = (NextPosition - CurPos).Size();
	// UE_LOG(LogTemp,Log,TEXT("%f"),size);
	// UE_LOG(LogTemp,Log,TEXT("%s"),*NextPosition.ToString());
	// UE_LOG(LogTemp,Log,TEXT("%s"),*CurPos.ToString());
	if( (NextPosition - CurPos).Size() < 1)
	{
		NextIndex++;
		SplineMapActor->MoveTo(this, NextIndex, NextPosition);
	}
}

void ATFirstAIController::Destroyed()
{
	Super::Destroyed();
	SplineMapActor->OnManDead();
}
