// Copyright Epic Games, Inc. All Rights Reserved.


#include "TowerDefenseGameModeBase.h"

#include "Character/Player/TPlayer.h"
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
}
