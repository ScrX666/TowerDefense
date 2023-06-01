// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/TThirdPlayerController.h"

#include "Component/ActorComp/TSoundManagerComponent.h"
#include "Component/ActorComp/TUIManagerComponent.h"
#include "Component/ActorComp/Player/TDialogComponent.h"

ATThirdPlayerController::ATThirdPlayerController()
{
	this->SetShowMouseCursor(false);
	SoundManagerComponent = CreateDefaultSubobject<UTSoundManagerComponent>(TEXT("SoundManager"));
	UIManagerComponent = CreateDefaultSubobject<UTUIManagerComponent>(TEXT("UIManager"));
	DialogComponent = CreateDefaultSubobject<UTDialogComponent>(TEXT("DialogManager"));
}
