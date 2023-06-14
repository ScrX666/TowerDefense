// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ActorComp/TMouseControlComponent.h"

#include "AI/Hero/THeroController.h"
#include "Building/TMainAttachBase.h"
#include "Building/TMainBuilding.h"
#include "Building/TPathEndBuilding.h"
#include "Building/Tower/TMainBeamTower.h"
#include "Building/Tower/TMainShotTower.h"
#include "Building/Tower/TMainTower.h"
#include "Character/THero.h"
#include "Component/ActorComp/TSkillManagerComponent.h"
#include "Component/ActorComp/TUIManagerComponent.h"
#include "Components/DecalComponent.h"
#include "GamePlay/TPlayerController.h"
#include "GamePlay/TPlayerState.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTMouseControlComponent::UTMouseControlComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

void UTMouseControlComponent::InitializeComponent()
{
	Super::InitializeComponent();
}


// Called when the game starts
void UTMouseControlComponent::BeginPlay()
{
	Super::BeginPlay();
	
	PC = Cast<ATPlayerController>(GetOwner());
	UIManagerComponent = Cast<UTUIManagerComponent>(GetOwner()->GetComponentByClass(UTUIManagerComponent::StaticClass()));
	SkillManagerComponent = Cast<UTSkillManagerComponent>(GetOwner()->GetComponentByClass(UTSkillManagerComponent::StaticClass()));
	TPlayerState = PC->GetPlayerState<ATPlayerState>();
	
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(this,ATHero::StaticClass(),Actors);
	if( Actors.Num())
	{
		ATHero* Hero = Cast<ATHero>(Actors[0]);
		if( Hero)
		{
			HeroAIC = Cast<ATHeroController>(Hero->GetController());
			if( HeroAIC)
			{
				HeroBlackboardComponent = HeroAIC->GetBlackboardComponent();
			}
		}
	}
	
	DecalComponent = UGameplayStatics::SpawnDecalAtLocation(this,DecalMaterial, FVector(50.0f), CursorLocation);
}
void UTMouseControlComponent::SetBuildingMode(TSubclassOf<AActor> BuildingCla)
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


/*
 * 准备执行技能
 */
void UTMouseControlComponent::ExecuteSkill(FName SkillName)
{
	BuildingMode = EBuildingMode::E_InSillMode;
	CurSkillName = SkillName;
	PC->CurrentMouseCursor = EMouseCursor::Hand;
	
	// 释放Skill为UI点击，不会立即更新，需要手动更新
	FInputModeGameOnly InputModeGameOnly;
	PC->SetInputMode(InputModeGameOnly);
}
/*
 * 确认执行技能
 */
void UTMouseControlComponent::ConfirmExecuteSkill()
{
	BuildingMode = EBuildingMode::E_NotInBuildMode;
	PC->CurrentMouseCursor = EMouseCursor::Default;

	// 不能在基座上释放技能
	if( HitResult.Actor->IsA(ATMainAttachBase::StaticClass())
		|| HitResult.Actor->IsA(ATMainTower::StaticClass()))
	{
		// 显示错误信息
		PC->OnShowMessage.Broadcast(EShowMessageType::E_SkillWrong);
	}
	else
	{
		SkillManagerComponent->Execute(CurSkillName);
	}

	// 释放Skill为UI点击，不会立即更新，需要手动更新
	FInputModeGameAndUI InputModeGameAndUI;
	InputModeGameAndUI.SetHideCursorDuringCapture(false);
	PC->SetInputMode(InputModeGameAndUI);
}
void UTMouseControlComponent::OnConstructTowerBulid(ATMainTower* Tower, bool bIsConstruct)
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
		SelectedBuilding = nullptr;
	}
}
/*
 * 绑定到输入事件 左键
 */
void UTMouseControlComponent::MouseClickDown()
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
					PC->OnShowMessage.Broadcast(EShowMessageType::E_CoinNotEnough);
				}
			}
			SetBuildingMode(nullptr);
		}
		break;
	case EBuildingMode::E_NotInBuildMode:
		{
			// 如果是塔 关闭UI面板
			if(SelectedBuilding && SelectedBuilding.GetObject()->IsA<ATMainBuilding>())
			{
				SelectedBuilding->OnSelected(false);
				SelectedBuilding = nullptr;
				UIManagerComponent->PopState();
			}

		
			if( CursorHitBuildingInterface)
			{
				//TODO: PathEndBuilding 添加显示UI
				if( CursorHitBuildingActor->IsA(ATPathEndBuilding::StaticClass()))
					break;
				
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
	case EBuildingMode::E_InHeroMode:
		// 控制英雄的模式
		if(HitResult.Actor != nullptr)
		{
			SelectedBuilding->OnSelected(false);
			if( HeroAIC)
				HeroAIC->HeroMove(HitResult.Location);
		}
		break;
	}
}
/*
 * 每一帧调用
 */
void UTMouseControlComponent::MouseMove(float Value)
{
#pragma region 获取鼠标碰撞信息
	ETraceTypeQuery Type = EBuildingMode::E_InBuildMode == BuildingMode ?
		TraceTypeQuery3 : TraceTypeQuery1;
	PC->GetHitResultUnderCursorByChannel(Type, true, HitResult);
	
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
			if( BuildingMode == EBuildingMode::E_InHeroMode)
			PC->CurrentMouseCursor = EMouseCursor::Crosshairs;
			else if( BuildingMode != EBuildingMode::E_InSillMode)
			{
				PC->CurrentMouseCursor = EMouseCursor::Default;
			}
		}
		//---------------------------------------- CursorHitBuildingActor 赋值
		CursorHitBuildingActor = Cast<AActor>(HitResult.Actor);
		CursorHitBuildingInterface = CursorHitBuildingActor;
		
		if( CursorHitBuildingInterface)
		{
			CursorHitBuildingInterface->OnHovered(true);
			// CursorManagerComponent->SetCursorType(this,EMouseCursor::Hand);
			PC->CurrentMouseCursor = EMouseCursor::Hand;
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

FVector UTMouseControlComponent::GetCursorHitLoc() const
{
	return HitResult.Location;
}

/*
 * 绑定到输入事件 右键 取消操作
 */
void UTMouseControlComponent::MouseRightClickDown()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("MouseRightClickDown"));
	switch( BuildingMode)
	{
	case EBuildingMode::E_InBuildMode:
		// 建造模式
		if( BuildingReferActor != nullptr)
		{
			SetBuildingMode(nullptr);
		}
		break;
	case EBuildingMode::E_NotInBuildMode:
		{
			// 如果是塔 关闭UI面板
			if(SelectedBuilding && SelectedBuilding.GetObject()->IsA<ATMainBuilding>())
			{
				SelectedBuilding->OnSelected(false);
				UIManagerComponent->PopState();
				SelectedBuilding = nullptr;
			}

			SelectedBuilding = nullptr;
		}
		break;
	case EBuildingMode::E_InSillMode:
		{
			BuildingMode = EBuildingMode::E_NotInBuildMode;
			PC->CurrentMouseCursor = EMouseCursor::Default;

			// 释放Skill为UI点击，不会立即更新，需要手动更新
			FInputModeGameAndUI InputModeGameAndUI;
			InputModeGameAndUI.SetHideCursorDuringCapture(false);
			PC->SetInputMode(InputModeGameAndUI);
		}
		break;
	case EBuildingMode::E_InHeroMode:
		// 控制英雄的模式
		if(HitResult.Actor != nullptr)
		{
			SelectedBuilding->OnSelected(false);
		}
		break;
	default: ;
	}
}

void UTMouseControlComponent::BuildingModeOff()
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

void UTMouseControlComponent::BuildingModeOn()
{
	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.Instigator = PC->GetPawn();
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	//------------------------------ BuildingRefer 赋值
	BuildingReferActor = GetWorld()->SpawnActor<AActor>(BuildingClass, CursorLocation,FRotator::ZeroRotator,ActorSpawnParameters);
	BuildingReferInterface = BuildingReferActor;
	DecalComponent->SetHiddenInGame(true);
	if( BuildingReferInterface)
	{
		BuildingReferInterface->OnSelected(BuildingMode == EBuildingMode::E_InBuildMode);
		BuildingReferInterface->OnConstruct(nullptr);
	}
}
/*
 * 绑定到Hero的OnSelectHero委托上
 */
void UTMouseControlComponent::OnSelectHero(bool bSelectHero)
{
	//bInHeroControlMode = bSelectHero;

	// 设置对应的Cursor
	if( bSelectHero == true)
	{
		BuildingMode = EBuildingMode::E_InHeroMode;
		// CursorManagerComponent->SetCursorType(this,EMouseCursor::Crosshairs);
		PC->CurrentMouseCursor = EMouseCursor::Crosshairs;
	}
	else
	{
		BuildingMode = EBuildingMode::E_NotInBuildMode;
		// CursorManagerComponent->SetCursorType(this,EMouseCursor::Default);
		PC->CurrentMouseCursor = EMouseCursor::Default;
	}
}
