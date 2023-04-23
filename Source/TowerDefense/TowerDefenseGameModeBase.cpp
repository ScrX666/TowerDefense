// Copyright Epic Games, Inc. All Rights Reserved.


#include "TowerDefenseGameModeBase.h"

#include "Character/Player/TPlayer.h"
#include "GamePlay/TPlayerController.h"

ATowerDefenseGameModeBase::ATowerDefenseGameModeBase()
{
	DefaultPawnClass = ATPlayer::StaticClass();
	PlayerControllerClass =	ATPlayerController::StaticClass();
}
