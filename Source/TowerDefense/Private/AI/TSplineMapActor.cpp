// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TSplineMapActor.h"

#include "AIController.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AI/TFirstAIController.h"
#include "Character/TManBase.h"
#include "GamePlay/TDataTableManager.h"

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
	//SpawnAI();
	SpawnWave();
	//GetWorld()->GetTimerManager().SetTimer(BeginplayTimerHandle,this,&ATSplineMapActor::SpawnWave,1,false);
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
			
			AActor* AIActor = GetWorld()->SpawnActor<AActor>(FaiSpawnStruct.AICharacter,SpawnLoc,SpawnRot,SpawnParameters);
			APawn* AiPawn = Cast<APawn>(AIActor);
			AiPawn->SpawnDefaultController();
			ATFirstAIController* moveController = Cast<ATFirstAIController >(AiPawn->GetController());
			if(ensure(moveController))
			moveController->SplineMapActor = this;
			// AIMove(moveController);
			MoveTo(moveController, 1, moveController->NextPosition);
			// FPlatformProcess::Sleep(0.5);
		

}

void ATSplineMapActor::SpawnWave()
{
	// && CurrentWave < TotalWaveCount
	// 如果当前已生成的敌人数量未达到本波敌人数量的上限
	if (CurrentEnemyCount < FaiSpawnStruct.SpawnAINums && CurrentWave != 0)
	{
		
		// 生成敌人
		SpawnAI();

		// 增加已生成的敌人数量
		CurrentEnemyCount++;

		// 设置计时器，等待一定时间后再生成下一个敌人
		GetWorld()->GetTimerManager().SetTimer(WaveTimerHandle, this, &ATSplineMapActor::SpawnWave, 1, false);
	}
	// 如果当前已生成的敌人数量已经达到本波敌人数量的上限
	else
	{
		if(CurrentWave < TDataTableManager::GetInstance()->GetAISpawnStructNum())
		{
			FaiSpawnStruct = TDataTableManager::GetInstance()->GetAISpawnStruct(CurrentWave);
			CurrentWave++;
			// 重置已生成的敌人数量
			CurrentEnemyCount = 0;

			// 取消计时器
			GetWorld()->GetTimerManager().ClearTimer(WaveTimerHandle);
		

			// 等待一段时间后生成下一波敌人
			GetWorld()->GetTimerManager().SetTimer(WaveTimerHandle, this, &ATSplineMapActor::SpawnWave, 2, false);
		}
		
		
	}
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


