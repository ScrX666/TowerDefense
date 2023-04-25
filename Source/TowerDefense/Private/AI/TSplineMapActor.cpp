// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TSplineMapActor.h"

// Sets default values
ATSplineMapActor::ATSplineMapActor()
{
 	SplineComponent = CreateDefaultSubobject<USplineComponent>("SplineComp");
}

// Called when the game starts or when spawned
void ATSplineMapActor::BeginPlay()
{
	Super::BeginPlay();
	SpawnAI();
}

void ATSplineMapActor::AddArrow()
{
	int SplinePointNums = SplineComponent->GetNumberOfSplinePoints();
	FInterpCurveVector SplinePos = SplineComponent->GetSplinePointsPosition();
	FInterpCurveQuat SplineRot = SplineComponent->GetSplinePointsRotation();

	for(int i=0; i<SplinePointNums-1;i++)
	{
		
	}
}

void ATSplineMapActor::AIMove(APawn* aiPawn)
{
	int SplinePointNums = SplineComponent->GetNumberOfSplinePoints();
	FInterpCurveVector SplinePos = SplineComponent->GetSplinePointsPosition();
	FInterpCurveQuat SplineRot = SplineComponent->GetSplinePointsRotation();
	
	for(int ToGoPoint = 1;ToGoPoint<=SplinePointNums;ToGoPoint++)
	{
		FVector FirstMoveLoc = SplineComponent->GetLocationAtSplineInputKey(ToGoPoint,ESplineCoordinateSpace::Local);
		aiPawn->AddMovementInput(FirstMoveLoc);
	}
	
	
}

void ATSplineMapActor::SpawnAI()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;//Ignore Collisions
	FVector SpawnLoc = SplineComponent->GetLocationAtSplineInputKey(0,ESplineCoordinateSpace::Local);
	FRotator SpawnRot = SplineComponent->GetRotationAtSplineInputKey(0,ESplineCoordinateSpace::Local);
	GetWorld()->SpawnActor<AActor>(BP_AICharacter,SpawnLoc,SpawnRot,SpawnParameters);
}



