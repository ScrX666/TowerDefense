// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/StackState/TStackState.h"

void UTStackState::EnterState(EStackAction StackAction)
{
	ReceiveEnterState(StackAction);
}

void UTStackState::ExitState(EStackAction StackAction)
{
	ReceiveExitState(StackAction);
}

void UTStackState::UpdateState(float DeltaTime)
{
	ReceiveUpdateState(DeltaTime);
}
