// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/TUIState.h"

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
