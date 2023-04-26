// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TSplineMapActor.h"

#include "AIController.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AI/TFirstAIController.h"

// Sets default values
ATSplineMapActor::ATSplineMapActor()
{
 	SplineComponent = CreateDefaultSubobject<USplineComponent>("SplineComp");
	
}

// Called when the game starts or when spawned
void ATSplineMapActor::BeginPlay()
{
	Super::BeginPlay();
	// TODO: Timer
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

void ATSplineMapActor::AIMove(ATFirstAIController* NPC)
{
	int SplinePointNums = SplineComponent->GetNumberOfSplinePoints();
	FInterpCurveVector SplinePos = SplineComponent->GetSplinePointsPosition();
	FInterpCurveQuat SplineRot = SplineComponent->GetSplinePointsRotation();
	
	// for(int ToGoPoint = 1;ToGoPoint<=SplinePointNums;ToGoPoint++)
	// {
	// 	FVector FirstMoveLoc = SplineComponent->GetLocationAtSplineInputKey(ToGoPoint,ESplineCoordinateSpace::World);
	//
	// 	if(NPC)
	// 	{
	// 		NPC->MoveToLocation(FirstMoveLoc);
	// 	}
	// 	
	// }
	if (NPC )
	{
		FVector StartLoc = NPC->GetPawn()->GetActorLocation();
		
		for (int ToGoPoint = 1; ToGoPoint <= SplinePointNums; ToGoPoint++)
		{
			FirstMoveLoc = SplineComponent->GetLocationAtSplineInputKey(ToGoPoint, ESplineCoordinateSpace::World);
			
			UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, StartLoc, FirstMoveLoc, NPC);
			if (NavPath && NavPath->IsValid())
			{
				FAIMoveRequest req;
				req.SetAcceptanceRadius(50);
				req.SetUsePathfinding(true);
				NPC->RequestMove(req,NavPath->GetPath());
				StartLoc = FirstMoveLoc;
			}
		}
	}



	
}

void ATSplineMapActor::SpawnAI()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;//Ignore Collisions
	FVector SpawnLoc = SplineComponent->GetLocationAtSplineInputKey(0,ESplineCoordinateSpace::World);
	FRotator SpawnRot = SplineComponent->GetRotationAtSplineInputKey(0,ESplineCoordinateSpace::World);
	AActor* AIActor = GetWorld()->SpawnActor<AActor>(BP_AICharacter,SpawnLoc,SpawnRot,SpawnParameters);
	
	APawn* AiPawn = Cast<APawn>(AIActor);
	AiPawn->SpawnDefaultController();
	ATFirstAIController* moveController = Cast<ATFirstAIController >(AiPawn->GetController());
	moveController->SplineMapActor = this;
	// AIMove(moveController);
	MoveTo(moveController, 1, moveController->NextPosition);
}

void ATSplineMapActor::MoveTo(ATFirstAIController* AIController, int index, FVector& NextPosition)
{
	FVector MoveLoc = SplineComponent->GetLocationAtSplineInputKey(index,ESplineCoordinateSpace::World);

	if(AIController)
	{
		UE_LOG(LogTemp,Log,TEXT("Spline %s"),*MoveLoc.ToString());
		AIController->MoveToLocation(MoveLoc,0,false);
	}
	NextPosition = MoveLoc;
}


