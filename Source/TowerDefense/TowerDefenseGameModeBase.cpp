// Copyright Epic Games, Inc. All Rights Reserved.


#include "TowerDefenseGameModeBase.h"

#include "Character/Player/TPlayer.h"
#include "GamePlay/THUD.h"
#include "GamePlay/TPlayerController.h"
#include "GamePlay/TPlayerState.h"

ATowerDefenseGameModeBase::ATowerDefenseGameModeBase()
{
	DefaultPawnClass = ATPlayer::StaticClass();
	PlayerControllerClass =	ATPlayerController::StaticClass();
	HUDClass = ATHUD::StaticClass();
	PlayerStateClass = ATPlayerState::StaticClass();
}
