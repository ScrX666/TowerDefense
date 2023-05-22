// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ActorComp/TCursorManagerComponent.h"

#include "Blueprint/UserWidget.h"

// Sets default values for this component's properties
UTCursorManagerComponent::UTCursorManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}
/*
 * 设置Cursor
 */
void UTCursorManagerComponent::SetCursorType(APlayerController* PC, EMouseCursor::Type CursorType)
{
	PC->CurrentMouseCursor = CursorType;
	
	if( CursorWidgets.Contains(CursorType))
	{
		return;
	}

	// 没有则创建
	if( CursorWidgetCla.Contains(CursorType) && !CursorWidgets.Contains(CursorType))
	{
		UUserWidget* CursorUI = CreateWidget(PC,CursorWidgetCla[CursorType]);
		CursorWidgets.Add(CursorType,CursorUI);
		PC->SetMouseCursorWidget(CursorType,CursorUI);
	}
		
}


// Called when the game starts
void UTCursorManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTCursorManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

