// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TSplineMapActor.h"

#include "AIController.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AI/TAIBaseController.h"
#include "AI/Enemy/TEnemyAIController.h"
#include "Building/TPathEndBuilding.h"
#include "Character/TManBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GamePlay/TDataTableManager.h"
#include "GamePlay/TPlayerController.h"
#include "GamePlay/TPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "TowerDefense/TowerDefenseGameModeBase.h"

// Sets default values
ATSplineMapActor::ATSplineMapActor()
{
 	SplineComponent = CreateDefaultSubobject<USplineComponent>("SplineComp");
	
}

// Called when the game starts or when spawned
void ATSplineMapActor::BeginPlay()
{
	Super::BeginPlay();

	if(bUseLevelNameAsTableSuffix)
	{
		// 使用关卡名查询
		TDataTableManager::GetInstance()->GetAISpawnStructs(
			FName(UGameplayStatics::GetCurrentLevelName(this)),AISpawnData);
	}
	else
	{
		// 使用自定义名字查询
		TDataTableManager::GetInstance()->GetAISpawnStructs(TableNameSuffix,AISpawnData);
	}
	
	SpawnWave();
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

void ATSplineMapActor::AIMove(ATAIBaseController* NPC)
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
	if(AIActor == nullptr) return ;
	APawn* AiPawn = Cast<APawn>(AIActor);
	AiPawn->SpawnDefaultController();
	ACharacter* AICharacter = Cast<ACharacter>(AIActor);
	if( AICharacter)
	{
		Cast<UCharacterMovementComponent>(AICharacter->GetMovementComponent())->MaxWalkSpeed = SpawnAIWalkSpeed;
	}
	ATEnemyAIController* moveController = Cast<ATEnemyAIController >(AiPawn->GetController());
	if(ensure(moveController))
	moveController->SplineMapActor = this;
	// AIMove(moveController);
	//MoveTo(moveController, 1, moveController->NextPosition); 原AI移动逻辑
	// FPlatformProcess::Sleep(0.5);
		
	CurrentExistEnemyCount++;
}

void ATSplineMapActor::SpawnWave()
{
	// UE_LOG(LogTemp,Log,TEXT("SpawnWave"));
	// && CurrentWave < TotalWaveCount
	// 如果当前已生成的敌人数量未达到本波敌人数量的上限
	if (CurrentEnemyCount < FaiSpawnStruct.SpawnAINums && CurrentWave != 0)
	{
		
		SpawnAIWalkSpeed = FaiSpawnStruct.ManWalkSpeed;
		if( CurrentEnemyCount == 0)
			OnWaveChanged.Broadcast(CurrentWave,AISpawnData.Num());
		
		// 生成敌人
		SpawnAI();
		// 增加已生成的敌人数量
		CurrentEnemyCount++;

		// 设置计时器，等待一定时间后再生成下一个敌人
		GetWorld()->GetTimerManager().SetTimer(WaveTimerHandle, this, &ATSplineMapActor::SpawnWave, FaiSpawnStruct.TimeBetweenSingle, false);
	}
	// 如果当前已生成的敌人数量已经达到本波敌人数量的上限
	else
	{
		if(CurrentWave < AISpawnData.Num())
		{
			FaiSpawnStruct = *AISpawnData[CurrentWave];
			CurrentWave++;
			// 重置已生成的敌人数量
			CurrentEnemyCount = 0;

			// 取消计时器
			GetWorld()->GetTimerManager().ClearTimer(WaveTimerHandle);
		

			// 等待一段时间后生成下一波敌人
			GetWorld()->GetTimerManager().SetTimer(WaveTimerHandle, this, &ATSplineMapActor::SpawnWave, FaiSpawnStruct.TimeBetweenWave, false);
		}
		else
		{
			//UE_LOG(LogTemp,Log,TEXT("bFinishSpawn CurrentWave %d GetAISpawnStructNum %d"),CurrentWave,TDataTableManager::GetInstance()->GetAISpawnStructNum());
			bFinishSpawn = true;
			// auto TDGameMode = Cast<ATowerDefenseGameModeBase>(UGameplayStatics::GetGameMode(this));
			// if(TDGameMode)
			// TDGameMode->OnGameEnd.Broadcast(true);
		}
		
	}
}
/*
 * 弃用 原AI移动逻辑
 */
void ATSplineMapActor::MoveTo(ATAIBaseController* AIController, int index, FVector& NextPosition)
{
	FVector MoveLoc = SplineComponent->GetLocationAtSplineInputKey(index,ESplineCoordinateSpace::World);

	if(AIController)
	{
		// UE_LOG(LogTemp,Log,TEXT("Spline %s"),*MoveLoc.ToString());
		AIController->MoveToLocation(MoveLoc,0,false);
	}
	NextPosition = MoveLoc;
}

void ATSplineMapActor::OnManDead()
{
	CurrentExistEnemyCount--;

	// 防止游戏结束 现存敌人销毁，引起的空指针引用
	if(!Cast<ATPlayerController>(UGameplayStatics::GetPlayerController(this,0)) ||
		Cast<ATowerDefenseGameModeBase>(UGameplayStatics::GetGameMode(this))->bGameEnd)
		return ;
	
	ATPlayerState* PlayerState = Cast<ATPlayerController>(UGameplayStatics::GetPlayerController(this,0))->TPlayerState;

	if( !PlayerState || !PlayerState->EndBuilding) return ;
	
	if( CurrentExistEnemyCount == 0 && bFinishSpawn && !PlayerState->EndBuilding->IsDead())
	{
		Cast<ATowerDefenseGameModeBase>(UGameplayStatics::GetGameMode(this))->OnGameEnd.Broadcast(true);
		PlayerState->AllEnemyDead = true;
	}
}

int32 ATSplineMapActor::GetMaxWaveCount()
{
	return AISpawnData.Num();
}

FVector ATSplineMapActor::GetTargetPos(int32 index)
{
	FVector NextPos = SplineComponent->GetLocationAtSplineInputKey(index,ESplineCoordinateSpace::World);
	return NextPos;
}


