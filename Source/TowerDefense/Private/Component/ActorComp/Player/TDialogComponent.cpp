// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ActorComp/Player/TDialogComponent.h"

// Sets default values for this component's properties
UTDialogComponent::UTDialogComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTDialogComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTDialogComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTDialogComponent::ExecuteDialogEvent(TSubclassOf<UObject> DialogEventCla)
{
	if( *DialogEventCla == nullptr)
	{
		UE_LOG(LogTemp,Log,TEXT("The class is empty"));
		return ;
	}
	if( !DialogEventCla->ImplementsInterface(UTDialogEventInterface::StaticClass()))
	{
		UE_LOG(LogTemp,Error,TEXT("The class dont implement dialogevent interface"));
		return ;
	}
	
	if( !DialogEvents.Contains(DialogEventCla))
	{
		DialogEvents.Add(DialogEventCla,NewObject<UObject>(this,DialogEventCla));
	}
	ITDialogEventInterface::Execute_TriggerDialogEvent(DialogEvents[DialogEventCla].GetObject(),GetWorld());
}

