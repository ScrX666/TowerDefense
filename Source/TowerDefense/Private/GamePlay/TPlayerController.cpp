// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/TPlayerController.h"

#include "Building/TMainAttachBase.h"
#include "Building/TMainBuilding.h"
#include "Building/Tower/TMainBeamTower.h"
#include "Building/Tower/TMainShotTower.h"
#include "Building/Tower/TMainTower.h"
#include "Component/ActorComp/TUIManagerComponent.h"
#include "Components/DecalComponent.h"
#include "GamePlay/TPlayerState.h"
#include "Kismet/GameplayStatics.h"


ATPlayerController::ATPlayerController() :
BuildingMode(EBuildingMode::E_NotInBuildMode), BuildingRefer(nullptr), CursorHitBuilding(nullptr)
{
	this->SetShowMouseCursor(true);
	UIManagerComponent = CreateDefaultSubobject<UTUIManagerComponent>(TEXT("UIManager"));
}

void ATPlayerController::SetBuildingMode(TSubclassOf<ATMainBuilding> BuildingCla)
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
		if( BuildingRefer != nullptr)
		{
			if( TPlayerState && TPlayerState->CoinsEnough(BuildingRefer->GetCostCoins()))
			{
				if( CanConstruct)
				{
					auto Building = GetWorld()->SpawnActor<ATMainBuilding>(BuildingClass,BuildingRefer->GetTransform());
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
			SetBuildingMode(nullptr);
		}
	}
	else
	{
		// 非建造模式
		if(SelectedBuilding)
		{
			SelectedBuilding->OnSelected(false);
			UIManagerComponent->PopState();
		}

		
		if( CursorHitBuilding)
		{
			CursorHitBuilding->OnSelected(true);
			SelectedBuilding = CursorHitBuilding;
			if( CursorHitBuilding->IsA<ATMainShotTower>())
				UIManagerComponent->PushUIState(TEXT("ShotTowerInfo"));
			if( CursorHitBuilding->IsA<ATMainBeamTower>())
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
	
	if( HitResult.bBlockingHit) CursorLocation = HitResult.Location;
	if( CursorHitBuilding != HitResult.Actor)
	{
		if( CursorHitBuilding != nullptr)
		{
			CursorHitBuilding->OnHovered(false);
		}
		CursorHitBuilding = Cast<ATMainBuilding>(HitResult.Actor);
		if( CursorHitBuilding)
			CursorHitBuilding->OnHovered(true);
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
	if( BuildingMode == EBuildingMode::E_InBuildMode && BuildingRefer != nullptr)
	{
		AttachBase = Cast<ATMainAttachBase>(HitResult.Actor);
		CanConstruct = false;
		if( AttachBase != nullptr)
		{
			if( AttachBase->AttachedBuilding != nullptr)
			{
				BuildingRefer->CanConstructBuilding(false);
				BuildingRefer->SetActorLocation(CursorLocation);
			}
			else
			{
				CanConstruct = true;
				BuildingRefer->CanConstructBuilding(true);
				BuildingRefer->SetActorLocation(AttachBase->AttachedBuildingPos->GetComponentLocation());
				BuildingRefer->SetActorRotation(AttachBase->AttachedBuildingPos->GetComponentRotation());
			}
		}
		else
		{
			BuildingRefer->CanConstructBuilding(false);
			BuildingRefer->SetActorLocation(CursorLocation);
		}
	}
#pragma endregion 
}

void ATPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UIManagerComponent->PushUIState(TEXT("TowerDefense"));
	//TODO 用事件替换
	EnableInput(this);
	TPlayerState = GetPlayerState<ATPlayerState>();
	DecalComponent = UGameplayStatics::SpawnDecalAtLocation(this,DecalMaterial, FVector(50.0f), CursorLocation);
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
	if( BuildingRefer)
	{
		UE_LOG(LogTemp,Log,TEXT("Destory Building"));
		if(BuildingRefer->Destroy())
		{
			UE_LOG(LogTemp,Log,TEXT("Destory Building Success"));
		}
		else
		{
			UE_LOG(LogTemp,Log,TEXT("Destory Building Fail"));
		}
		BuildingRefer = nullptr;
	}
}

void ATPlayerController::BuildingModeOn()
{
	BuildingRefer = GetWorld()->SpawnActor<ATMainBuilding>(BuildingClass, CursorLocation,FRotator::ZeroRotator);
	BuildingRefer->OnSelected(BuildingMode == EBuildingMode::E_InBuildMode);
	DecalComponent->SetHiddenInGame(true);
	if( BuildingRefer->Implements<UTBuildingInterface>())
	{
		BuildingRefer->OnConstruct(nullptr);
	}
}
