// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/TUIState.h"

#include "Component/ActorComp/TUIManagerComponent.h"
#include "Component/ActorComp/Player/TDialogComponent.h"
#include "GamePlay/TPlayerController.h"
#include "GamePlay/TThirdPlayerController.h"
#include "Kismet/GameplayStatics.h"

void UTUIState::ReceiveEnterState_Implementation(EStackAction StackAction)
{
	switch (StackAction)
	{
	case Push:
		{
			AddToViewport();
			break;
		}
	case Pop:
		{
			SetVisibility(ESlateVisibility::Visible);
			break;
		}
	}
}

void UTUIState::ReceiveExitState_Implementation(EStackAction StackAction)
{
	switch (StackAction)
	{
	case Push:
		{
			SetVisibility(ESlateVisibility::Hidden);
			break;
		}
	case Pop:
		{
			RemoveFromParent();
			break;
		}
	}
}

void UTUIState::ReceiveUpdateState_Implementation(float DeltaTime)
{
}

void UTUIState::NativeConstruct()
{
	Super::NativeConstruct();

	PC = UGameplayStatics::GetPlayerController(this, 0);
	TowerDefensePC = Cast<ATPlayerController>(PC);
	ThirdPlayerPC = Cast<ATThirdPlayerController>(PC);
	if( PC)
	{
		UIManagerComponent = Cast<UTUIManagerComponent>(PC->GetComponentByClass(UTUIManagerComponent::StaticClass()));
		DialogManagerComponent = Cast<UTDialogComponent>(PC->GetComponentByClass(UTDialogComponent::StaticClass()));
	}
}

void UTUIState::EnterState(EStackAction StackAction)
{
	ReceiveEnterState(StackAction);
}

void UTUIState::ExitState(EStackAction StackAction)
{
	ReceiveExitState(StackAction);
}

void UTUIState::UpdateState(float DeltaTime)
{
	ReceiveUpdateState(DeltaTime);
}
