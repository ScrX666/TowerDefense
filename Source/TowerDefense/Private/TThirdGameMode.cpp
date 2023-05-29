// Fill out your copyright notice in the Description page of Project Settings.


#include "TThirdGameMode.h"

#include "Character/Player/TThirdCharacter.h"
#include "GamePlay/TGameState.h"
#include "GamePlay/THUD.h"
#include "GamePlay/TPlayerState.h"
#include "GamePlay/TThirdPlayerController.h"

ATThirdGameMode::ATThirdGameMode()
{
	DefaultPawnClass = ATThirdCharacter::StaticClass();
	PlayerControllerClass =	ATThirdPlayerController::StaticClass();
	HUDClass = ATHUD::StaticClass();
	PlayerStateClass = ATPlayerState::StaticClass();
	GameStateClass = ATGameState::StaticClass();
}
