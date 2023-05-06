// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ActorComp/TUIManagerComponent.h"

#include "Blueprint/UserWidget.h"
#include "GamePlay/TUIState.h"
#include "Kismet/GameplayStatics.h"

void UTUIManagerComponent::InitUIState_Implementation()
{
	auto PlayerControl = UGameplayStatics::GetPlayerController(GetOwner(),0);
	if( !PlayerControl->IsLocalController())
	{
		return ;
	}
	for(TTuple<FName,TSubclassOf<UTUIState>> UI : UIStates)
	{
		auto Widget = CreateWidget<UTUIState>(PlayerControl,UI.Value.Get(),UI.Key);
		UIInstances.Add(UI.Key,Widget);
	}
}

UTUIState* UTUIManagerComponent::GetUI_Implementation(FName Name)
{
	UTUIState** UI = UIInstances.Find(Name);
	if( UI != nullptr)
	{
		return *UI;
	}

	return nullptr;
}

void UTUIManagerComponent::PushUIState(FName UIName)
{
	auto UI = GetUI(UIName);
	if( UI == nullptr) return ;

	TScriptInterface<ITStackStateInterface> Interface(UI);
	
	PushState(Interface);
}

void UTUIManagerComponent::GetCurrentUIState(TSubclassOf<UTUIState> StateClass,
	TEnumAsByte<EUIStateCastResult>& IsVaild, UTUIState*& OutState)
{
	if( StateCount() <= 0)
	{
		IsVaild = Failure;
		return ;
	}
	UTUIState* State = Cast<UTUIState>(GetCurrentState().GetObject());
	IsVaild = State != nullptr && State->GetClass()->IsChildOf(StateClass) ? Success : Failure;
	if( IsVaild == Success)
	{
		OutState = State;
	}
}

void UTUIManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	InitUIState();
}

void UTUIManagerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}
