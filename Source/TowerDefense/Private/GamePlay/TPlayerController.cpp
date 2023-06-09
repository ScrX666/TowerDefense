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
#include "Component/ActorComp/TMouseControlComponent.h"
#include "Component/ActorComp/TSkillManagerComponent.h"
#include "Component/ActorComp/TSoundManagerComponent.h"
#include "Component/ActorComp/TUIManagerComponent.h"
#include "Component/ActorComp/Player/TDialogComponent.h"
#include "Components/DecalComponent.h"
#include "GamePlay/TGameState.h"
#include "GamePlay/TPlayerState.h"
#include "GamePlay/TUIState.h"
#include "Kismet/GameplayStatics.h"
#include "TowerDefense/TowerDefenseGameModeBase.h"


ATPlayerController::ATPlayerController()
{
	this->SetShowMouseCursor(true);
	UIManagerComponent = CreateDefaultSubobject<UTUIManagerComponent>(TEXT("UIManager"));
	SkillManagerComponent = CreateDefaultSubobject<UTSkillManagerComponent>(TEXT("SkillManager"));
	SoundManagerComponent = CreateDefaultSubobject<UTSoundManagerComponent>(TEXT("SoundManager"));
	DialogComponent = CreateDefaultSubobject<UTDialogComponent>(TEXT("DialogManager"));
	MouseControlComponent = CreateDefaultSubobject<UTMouseControlComponent>(TEXT("MouseControlManager"));
	// CursorManagerComponent = CreateDefaultSubobject<UTCursorManagerComponent>(TEXT("CursorManager"));
}


void ATPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	// 绑定开始游戏
	ATowerDefenseGameModeBase* TDGameMode = Cast<ATowerDefenseGameModeBase>(UGameplayStatics::GetGameMode(this));
	if( TDGameMode)
	TDGameMode->OnGameStart.AddDynamic(this, &ATPlayerController::OnGameReallyStart);
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
			Hero->OnSelectHero.AddDynamic(MouseControlComponent,&UTMouseControlComponent::OnSelectHero);
			Hero->OnSelectHero.AddDynamic(SoundManagerComponent,&UTSoundManagerComponent::OnSelectHero);
			HeroAIC = Cast<ATHeroController>(Hero->GetController());
			if( HeroAIC)
			{
				HeroBlackboardComponent = HeroAIC->GetBlackboardComponent();
			}
		}
	}
	
	
	EnableInput(this);
	TPlayerState = GetPlayerState<ATPlayerState>();

	
	// 绑定结束事件
	ATowerDefenseGameModeBase* GameMode = Cast<ATowerDefenseGameModeBase>(UGameplayStatics::GetGameMode(this));
	if( GameMode)
	{
		GameMode->OnGameEnd.AddDynamic(this,&ATPlayerController::OnGameEnd);
		GameMode->OnGameEnd.AddDynamic(SoundManagerComponent,&UTSoundManagerComponent::OnGameEnd);
	}

	MouseControlComponent->OnConstructTower.AddDynamic(MouseControlComponent,&UTMouseControlComponent::OnConstructTowerBulid);
	MouseControlComponent->OnConstructTower.AddDynamic(SoundManagerComponent,&UTSoundManagerComponent::OnConstructTowerBulid);
	
	// 设置Cursor
	// CursorManagerComponent->SetCursorType(this,EMouseCursor::Default);
	CurrentMouseCursor = EMouseCursor::Default;
}
/*
 * ESC 按键
 */
void ATPlayerController::OnEscBtnPress()
{
	UIManagerComponent->OnESCPress();
}


void ATPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("MouseClick"), IE_Pressed, MouseControlComponent, &UTMouseControlComponent::MouseClickDown);
	InputComponent->BindAction(TEXT("Cancel"), IE_Pressed, MouseControlComponent, &UTMouseControlComponent::MouseRightClickDown);
	InputComponent->BindAxis(TEXT("MouseMove"), MouseControlComponent, &UTMouseControlComponent::MouseMove);
	//InputComponent->BindAction(TEXT("ESC"), IE_Pressed, this,&ATPlayerController::OnEscBtnPress);
}

/*
 * 绑定到GameMode 的 OnGameEnd
 */
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
 * 绑定到GameMode 的 OnGameReallyStart
 */
void ATPlayerController::OnGameReallyStart()
{
	if( UGameplayStatics::GetCurrentLevelName(GetWorld()) == TEXT("Map_Start"))
		UIManagerComponent->PushUIState(TEXT("BeginUI"));
	else
		UIManagerComponent->PushUIState(TEXT("TowerDefense"));
}
