// Copyright Epic Games, Inc. All Rights Reserved.


#include "TowerDefenseGameModeBase.h"

#include "Character/Player/TPlayer.h"
#include "Components/AudioComponent.h"
#include "GamePlay/TDataTableManager.h"
#include "GamePlay/TGameInstance.h"
#include "GamePlay/TGameState.h"
#include "GamePlay/THUD.h"
#include "GamePlay/TPlayerController.h"
#include "GamePlay/TPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

ATowerDefenseGameModeBase::ATowerDefenseGameModeBase()
{
	DefaultPawnClass = ATPlayer::StaticClass();
	PlayerControllerClass =	ATPlayerController::StaticClass();
	HUDClass = ATHUD::StaticClass();
	PlayerStateClass = ATPlayerState::StaticClass();
	GameStateClass = ATGameState::StaticClass();
}

void ATowerDefenseGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	OnGameEnd.AddDynamic(this, &ATowerDefenseGameModeBase::GameEnd);
}


void ATowerDefenseGameModeBase::GameEnd(bool IsWin)
{
	bGameEnd = true;
	UGameplayStatics::SetGamePaused(this,true);
	if( IsWin)
	{
		// 赢得此关卡，添加新的可建筑的塔
		UTGameInstance* GameInstance = Cast<UTGameInstance>(GetGameInstance());
		if( GameInstance)
		{
			TArray<TSubclassOf<ATMainTower>> AddTowers = TDataTableManager::GetInstance()->GetWinTowers(
				FName(UGameplayStatics::GetCurrentLevelName(this)));
			for( const auto& Tower : AddTowers)
			{
				GameInstance->AddTower(Tower);
			}
		}
	}
}
