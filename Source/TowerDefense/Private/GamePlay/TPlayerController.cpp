// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/TPlayerController.h"

#include "AIController.h"
#include "Building/TMainAttachBase.h"
#include "Building/TMainBuilding.h"
#include "Building/Tower/TMainBeamTower.h"
#include "Building/Tower/TMainShotTower.h"
#include "Building/Tower/TMainTower.h"
#include "Character/TSoldierBase.h"
#include "Component/ActorComp/TUIManagerComponent.h"
#include "Components/DecalComponent.h"
#include "GamePlay/TGameState.h"
#include "GamePlay/TPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "TowerDefense/TowerDefenseGameModeBase.h"


ATPlayerController::ATPlayerController() :
BuildingMode(EBuildingMode::E_NotInBuildMode)
{
	this->SetShowMouseCursor(true);
	UIManagerComponent = CreateDefaultSubobject<UTUIManagerComponent>(TEXT("UIManager"));
}

void ATPlayerController::SetBuildingMode(TSubclassOf<AActor> BuildingCla)
{
	this->BuildingClass = BuildingCla;
	if( BuildingMode == EBuildingMode::E_InBuildMode)
	{
		// 放下
		BuildingMode = EBuildingMode::E_NotInBuildMode;
		BuildingModeOff();
	}
	else
	{
		// 拿起
		BuildingMode = EBuildingMode::E_InBuildMode;
		BuildingModeOn();
	}
}

void ATPlayerController::MouseClickDown()
{
	if( EBuildingMode::E_InBuildMode == BuildingMode)
	{
		// 建造模式
		if( BuildingReferActor != nullptr)
		{
			if( BuildingReferActor->IsA<ATMainBuilding>())
			{
				// 建造 建筑物
				if( TPlayerState && TPlayerState->CoinsEnough(BuildingReferInterface->GetCostCoins()))
				{
					if( CanConstruct)
					{
						auto Building = GetWorld()->SpawnActor<ATMainBuilding>(BuildingClass,BuildingReferActor->GetTransform());
						Building->OnSelected(false);
						AttachBase->OnConstructAttachBuilding(Building);
						Building->OnConstruct(AttachBase);
						TPlayerState->RemoveCoins(Building->GetCostCoins());
					}
					else
					{
						UE_LOG(LogTemp,Log,TEXT("Build ERROR"));
					}
				}
				else
				{
				
				}
			}
			else
			{
				// 创建 角色
				if( TPlayerState && TPlayerState->CoinsEnough(BuildingReferInterface->GetCostCoins()))
				{
					if( CanConstruct)
					{
						auto Building = GetWorld()->SpawnActor<ATSoldierBase>(BuildingClass,BuildingReferActor->GetTransform());
						Building->OnSelected(false);
						Building->OnConstruct(nullptr);
						TPlayerState->RemoveCoins(Building->GetCostCoins());
					}
					else
					{
						UE_LOG(LogTemp,Log,TEXT("Build ERROR"));
					}
				}
				else
				{
				
				}
			}
			SetBuildingMode(nullptr);
		}
	}
	else
	{
		// 非建造模式 点击
		if(SelectedBuilding)
		{
			SelectedBuilding->OnSelected(false);
			UIManagerComponent->PopState();
		}

		
		if( CursorHitBuildingActor)
		{
			CursorHitBuildingInterface->OnSelected(true);
			SelectedBuilding = Cast<ATMainBuilding>(CursorHitBuildingActor);
			if( CursorHitBuildingActor->IsA<ATMainShotTower>())
				UIManagerComponent->PushUIState(TEXT("ShotTowerInfo"));
			if( CursorHitBuildingActor->IsA<ATMainBeamTower>())
				UIManagerComponent->PushUIState(TEXT("BeamTowerInfo"));
		}
		else
		{
			SelectedBuilding = nullptr;
		}
	}
}

void ATPlayerController::MouseMove(float Value)
{
#pragma region 获取鼠标碰撞信息
	FHitResult HitResult;
	ETraceTypeQuery Type = EBuildingMode::E_InBuildMode == BuildingMode ?
		TraceTypeQuery3 : TraceTypeQuery1;
	GetHitResultUnderCursorByChannel(Type, true, HitResult);
	
	if( HitResult.bBlockingHit)
	{
		CursorLocation = HitResult.Location;
	}
	if( CursorHitBuildingActor != HitResult.Actor)
	{
		if( CursorHitBuildingActor != nullptr)
		{
			CursorHitBuildingInterface->OnHovered(false);
		}
		//---------------------------------------- CursorHitBuildingActor 赋值
		CursorHitBuildingActor = Cast<ATMainBuilding>(HitResult.Actor);
		CursorHitBuildingInterface = Cast<ATMainBuilding>(HitResult.Actor);
		
		if( CursorHitBuildingActor)
			CursorHitBuildingInterface->OnHovered(true);
	}
#pragma endregion

#pragma region 设置贴画
	if( DecalComponent != nullptr)
		DecalComponent->SetWorldLocation(CursorLocation);
	else
	{
		UE_LOG(LogTemp,Log, TEXT("Decal NULL"));
	}
#pragma endregion 
	
#pragma region 设置建筑物位置
	if( BuildingMode == EBuildingMode::E_InBuildMode && BuildingReferActor != nullptr)
	{
		if(BuildingReferActor->IsA<ATMainBuilding>())
		{
			// 建筑物
			AttachBase = Cast<ATMainAttachBase>(HitResult.Actor);
			CanConstruct = false;
			if( AttachBase != nullptr)
			{
				if( AttachBase->AttachedBuilding != nullptr)
				{
					BuildingReferInterface->CanConstructBuilding(false);
					BuildingReferActor->SetActorLocation(CursorLocation);
				}
				else
				{
					CanConstruct = true;
					BuildingReferInterface->CanConstructBuilding(true);
					BuildingReferActor->SetActorLocation(AttachBase->AttachedBuildingPos->GetComponentLocation());
					BuildingReferActor->SetActorRotation(AttachBase->AttachedBuildingPos->GetComponentRotation());
				}
			}
			else
			{
				BuildingReferInterface->CanConstructBuilding(false);
				BuildingReferActor->SetActorLocation(CursorLocation);
			}
		}
		else
		{
			// 创建角色
			CanConstruct = false;
			if( HitResult.Actor.IsValid())
			{
				CanConstruct = true;
				BuildingReferInterface->CanConstructBuilding(true);
				BuildingReferActor->SetActorLocation(CursorLocation);
			}
			else
			{
				BuildingReferInterface->CanConstructBuilding(false);
				BuildingReferActor->SetActorLocation(CursorLocation);
			}
		}
	}
#pragma endregion 
}

void ATPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if( UGameplayStatics::GetCurrentLevelName(GetWorld()) == TEXT("Map_Start"))
		UIManagerComponent->PushUIState(TEXT("BeginUI"));
	else
		UIManagerComponent->PushUIState(TEXT("TowerDefense"));
	//TODO 用事件替换
	EnableInput(this);
	TPlayerState = GetPlayerState<ATPlayerState>();
	DecalComponent = UGameplayStatics::SpawnDecalAtLocation(this,DecalMaterial, FVector(50.0f), CursorLocation);

	// 绑定结束事件
	ATowerDefenseGameModeBase* GameMode = Cast<ATowerDefenseGameModeBase>(UGameplayStatics::GetGameMode(this));
	if( GameMode)
	{
		GameMode->OnGameEnd.AddDynamic(this,&ATPlayerController::OnGameEnd);
	}
}

void ATPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("MouseClick"), IE_Pressed, this, &ATPlayerController::MouseClickDown);
	InputComponent->BindAxis(TEXT("MouseMove"), this, &ATPlayerController::MouseMove);
}

void ATPlayerController::BuildingModeOff()
{
	DecalComponent->SetHiddenInGame(false);
	if( BuildingReferActor)
	{
		UE_LOG(LogTemp,Log,TEXT("Destory Building"));
		if( BuildingReferActor)
		{
			if(BuildingReferActor->Destroy())
			{
				UE_LOG(LogTemp,Log,TEXT("Destory Building Success"));
			}
			else
			{
				UE_LOG(LogTemp,Log,TEXT("Destory Building Fail"));
			}
		}
		//------------------------------ BuildingRefer 赋值
		BuildingReferInterface = nullptr;
		BuildingReferActor = nullptr;
	}
}

void ATPlayerController::BuildingModeOn()
{
	//------------------------------ BuildingRefer 赋值
	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.Instigator = this->GetPawn();
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	BuildingReferActor = GetWorld()->SpawnActor<AActor>(BuildingClass, CursorLocation,FRotator::ZeroRotator,ActorSpawnParameters);
	BuildingReferInterface = BuildingReferActor;
	DecalComponent->SetHiddenInGame(true);
	if( BuildingReferInterface)
	{
		BuildingReferInterface->OnSelected(BuildingMode == EBuildingMode::E_InBuildMode);
		BuildingReferInterface->OnConstruct(nullptr);
	}
}

void ATPlayerController::OnGameEnd(bool IsWin)
{
	ATGameState* GameState = Cast<ATGameState>(UGameplayStatics::GetGameState(this));
	if( GameState)
	{
		// 留给 UI 使用
		GameState->bIsWin = IsWin;
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("GameState is Not TGameState"));
	}
	UIManagerComponent->PushUIState(TEXT("EndGame"));
	// UIManagerComponent->GetCurrentUIState()
}
