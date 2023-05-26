// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/TPlayerController.h"

#include "AIController.h"
#include "AI/Hero/THeroController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Building/TMainAttachBase.h"
#include "Building/TMainBuilding.h"
#include "Building/Tower/TMainBeamTower.h"
#include "Building/Tower/TMainShotTower.h"
#include "Building/Tower/TMainTower.h"
#include "Character/THero.h"
#include "Character/TSoldierBase.h"
#include "Component/ActorComp/TCursorManagerComponent.h"
#include "Component/ActorComp/TSkillManagerComponent.h"
#include "Component/ActorComp/TSoundManagerComponent.h"
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
	SkillManagerComponent = CreateDefaultSubobject<UTSkillManagerComponent>(TEXT("SkillManager"));
	SoundManagerComponent = CreateDefaultSubobject<UTSoundManagerComponent>(TEXT("SoundManager"));
	// CursorManagerComponent = CreateDefaultSubobject<UTCursorManagerComponent>(TEXT("CursorManager"));
}

void ATPlayerController::OnConstructTowerBulid(ATMainTower* Tower, bool bIsConstruct)
{
	if( bIsConstruct)
	{
		Tower->OnSelected(false);
		AttachBase->OnConstructAttachBuilding(Tower);
		Tower->OnConstruct(AttachBase);
		TPlayerState->RemoveCoins(Tower->GetCostCoins());
	}
	else
	{
		Tower->OnDestory();
	}
}

void ATPlayerController::SetBuildingMode(TSubclassOf<AActor> BuildingCla)
{
	if(BuildingMode == EBuildingMode::E_InSillMode) return ;
	
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

void ATPlayerController::ExecuteSkill(FName SkillName)
{
	BuildingMode = EBuildingMode::E_InSillMode;
	CurSkillName = SkillName;
	CurrentMouseCursor = EMouseCursor::Hand;
	// 释放Skill为UI点击，不会立即更新，需要手动更新
	if(bIsTest)
	{
		SetInputMode(FInputModeGameOnly());
	}
}

void ATPlayerController::ConfirmExecuteSkill()
{
	BuildingMode = EBuildingMode::E_NotInBuildMode;
	CurrentMouseCursor = EMouseCursor::Default;
	SkillManagerComponent->Execute(CurSkillName);
	if(bIsTest)
	{
		SetInputMode(FInputModeGameAndUI());
	}
}

void ATPlayerController::MouseClickDown()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("MouseClickDown"));
	switch( BuildingMode)
	{
	case EBuildingMode::E_InBuildMode:
		// 建造模式
		if( BuildingReferActor != nullptr)
		{
			if( BuildingReferActor->IsA<ATMainBuilding>())
			{
				// 建造 建筑物
				if( TPlayerState && TPlayerState->CoinsEnough(BuildingReferInterface->GetCostCoins()))
				{
					if( bCanConstruct)
					{
						auto Building = GetWorld()->SpawnActor<ATMainTower>(BuildingClass,BuildingReferActor->GetTransform());
						OnConstructTower.Broadcast(Building,true);
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
		break;
	case EBuildingMode::E_NotInBuildMode:
		// 非建造模式 点击
		if(bInHeroControlMode)
		{
			// 控制英雄的模式
			if(HitResult.Actor != nullptr)
			{
				SelectedBuilding->OnSelected(false);
				if( HeroAIC)
				HeroAIC->HeroMove(HitResult.Location);
			}
		}
		else
		{
			// 如果是塔 关闭UI面板
			if(SelectedBuilding && SelectedBuilding.GetObject()->IsA<ATMainBuilding>())
			{
				SelectedBuilding->OnSelected(false);
				UIManagerComponent->PopState();
			}

		
			if( CursorHitBuildingInterface)
			{
				CursorHitBuildingInterface->OnSelected(true);
				SelectedBuilding = CursorHitBuildingActor;
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
		break;
	case EBuildingMode::E_InSillMode:
		ConfirmExecuteSkill();
		break;
	}
}

void ATPlayerController::MouseMove(float Value)
{
#pragma region 获取鼠标碰撞信息
	ETraceTypeQuery Type = EBuildingMode::E_InBuildMode == BuildingMode ?
		TraceTypeQuery3 : TraceTypeQuery1;
	GetHitResultUnderCursorByChannel(Type, true, HitResult);
	
	if( HitResult.bBlockingHit)
	{
		CursorLocation = HitResult.Location;
	}
	if( CursorHitBuildingActor != HitResult.Actor)
	{
		if( CursorHitBuildingInterface)
		{
			CursorHitBuildingInterface->OnHovered(false);
			// CursorManagerComponent->SetCursorType(this,EMouseCursor::Default);
			if( bInHeroControlMode)
			CurrentMouseCursor = EMouseCursor::Crosshairs;
			else if( BuildingMode != EBuildingMode::E_InSillMode)
			{
				CurrentMouseCursor = EMouseCursor::Default;
			}
		}
		//---------------------------------------- CursorHitBuildingActor 赋值
		CursorHitBuildingActor = Cast<AActor>(HitResult.Actor);
		CursorHitBuildingInterface = CursorHitBuildingActor;
		
		if( CursorHitBuildingInterface)
		{
			CursorHitBuildingInterface->OnHovered(true);
			// CursorManagerComponent->SetCursorType(this,EMouseCursor::Hand);
			CurrentMouseCursor = EMouseCursor::Hand;
		}
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
			bCanConstruct = false;
			if( AttachBase != nullptr)
			{
				if( IsValid(AttachBase->AttachedBuilding))
				{
					BuildingReferInterface->CanConstructBuilding(false);
					BuildingReferActor->SetActorLocation(CursorLocation);
				}
				else
				{
					bCanConstruct = true;
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
			bCanConstruct = false;
			if( HitResult.Actor.IsValid())
			{
				bCanConstruct = true;
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

FVector ATPlayerController::GetCursorHitLoc() const
{
	return HitResult.Location;
}

void ATPlayerController::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(this,ATHero::StaticClass(),Actors);
	if( Actors.Num())
	{
		ATHero* Hero = Cast<ATHero>(Actors[0]);
		if( Hero)
		{
			Hero->OnSelectHero.AddDynamic(this,&ATPlayerController::OnSelectHero);
			Hero->OnSelectHero.AddDynamic(SoundManagerComponent,&UTSoundManagerComponent::OnSelectHero);
			HeroAIC = Cast<ATHeroController>(Hero->GetController());
			if( HeroAIC)
			{
				HeroBlackboardComponent = HeroAIC->GetBlackboardComponent();
			}
		}
	}
	
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
		GameMode->OnGameEnd.AddDynamic(SoundManagerComponent,&UTSoundManagerComponent::OnGameEnd);
	}

	OnConstructTower.AddDynamic(this,&ATPlayerController::OnConstructTowerBulid);
	OnConstructTower.AddDynamic(SoundManagerComponent,&UTSoundManagerComponent::OnConstructTowerBulid);
	
	// 设置Cursor
	// CursorManagerComponent->SetCursorType(this,EMouseCursor::Default);
	CurrentMouseCursor = EMouseCursor::Default;
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

void ATPlayerController::OnGameEnd(bool bIsWin)
{
	ATGameState* GameState = Cast<ATGameState>(UGameplayStatics::GetGameState(this));
	if( GameState)
	{
		// 留给 UI 使用
		GameState->bIsWin = bIsWin;
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("GameState is Not TGameState"));
	}
	UIManagerComponent->PushUIState(TEXT("EndGame"));
	// UIManagerComponent->GetCurrentUIState()
}
/*
 * 绑定到Hero的OnSelectHero委托上
 */
void ATPlayerController::OnSelectHero(bool bSelectHero)
{
	bInHeroControlMode = bSelectHero;

	// 设置对应的Cursor
	if( bSelectHero == true)
	{
		// CursorManagerComponent->SetCursorType(this,EMouseCursor::Crosshairs);
		CurrentMouseCursor = EMouseCursor::Crosshairs;
	}
	else
	{
		// CursorManagerComponent->SetCursorType(this,EMouseCursor::Default);
		CurrentMouseCursor = EMouseCursor::Default;
	}
}
