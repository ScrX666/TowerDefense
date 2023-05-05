// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ActorComp/TStackStateMachineComponent.h"

// Sets default values for this component's properties
UTStackStateMachineComponent::UTStackStateMachineComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


TScriptInterface<ITStackStateInterface> UTStackStateMachineComponent::GetCurrentState()
{
	return States[StateCount() - 1];
}

TScriptInterface<ITStackStateInterface> UTStackStateMachineComponent::GetUnderState()
{
	return States[StateCount() - 2];
}

TScriptInterface<ITStackStateInterface> UTStackStateMachineComponent::GetState(int32 Index)
{
	return States[Index];
}

int32 UTStackStateMachineComponent::StateCount() const
{
	return States.Num();
}

float UTStackStateMachineComponent::GetCurrentStateTime() const
{
	return CurrentStateTime;
}

// Called when the game starts
void UTStackStateMachineComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UTStackStateMachineComponent::StatePushed(TScriptInterface<ITStackStateInterface> PushedState)
{
	// 广播
	if( OnStatePushed.IsBound())
	{
		OnStatePushed.Broadcast(PushedState);
	}
	// 蓝图
	ReceiveStatePushed(PushedState);
}

void UTStackStateMachineComponent::StatePopped(TScriptInterface<ITStackStateInterface> PoppedState)
{
	// 广播
	if( OnStatePopped.IsBound())
	{
		OnStatePopped.Broadcast(PoppedState);
	}
	// 蓝图
	ReceiveStatePopped(PoppedState);
}


// Called every frame
void UTStackStateMachineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if( StateCount() > 0 && GetCurrentState() != nullptr)
	{
		GetCurrentState()->UpdateState(DeltaTime);
	}
}

void UTStackStateMachineComponent::PushState(TScriptInterface<ITStackStateInterface> NewState)
{
	if( StateCount() > 0)
	{
		auto CurrentState = GetCurrentState();
		if( CurrentState != nullptr)
		{
			// 覆盖当前状态，即退出状态
			CurrentState->ExitState(Push);
		}
	}
	CurrentStateTime = 0.0f;
	States.Push(NewState);
	NewState->EnterState(Push);

	// 由子类调用
	StatePushed(NewState);
}

void UTStackStateMachineComponent::PopState()
{
	auto OriginState = GetCurrentState();
	if( OriginState != nullptr)
	{
		OriginState->ExitState(Pop);
	}
	States.Pop();
	CurrentStateTime = 0;
	if( StateCount() > 0)
	{
		// 更新新栈顶的状态
		GetCurrentState()->EnterState(Pop);
	}

	// 由子类调用
	StatePopped(OriginState);
}

void UTStackStateMachineComponent::PopStates(int Count)
{
	while(Count > 0)
	{
		PopState();
		Count--;
	}
}

void UTStackStateMachineComponent::PopAllStates()
{
	PopStates(StateCount());
}

void UTStackStateMachineComponent::EnterState(EStackAction StackAction)
{
	// 广播
	if( OnStateEnter.IsBound())
	{
		OnStateEnter.Broadcast();
	}
	// 蓝图
	ReceiveEnterState(StackAction);
}

void UTStackStateMachineComponent::ExitState(EStackAction StackAction)
{
	// 广播
	if( OnStateExit.IsBound())
	{
		OnStateExit.Broadcast();
	}
	// 蓝图
	ReceiveExitState(StackAction);
}

void UTStackStateMachineComponent::UpdateState(float DeltaTime)
{
	ReceiveUpdateState(DeltaTime);
	CurrentStateTime += DeltaTime;
	if( StateCount() > 0)
	{
		GetCurrentState()->UpdateState(DeltaTime);
	}
}

