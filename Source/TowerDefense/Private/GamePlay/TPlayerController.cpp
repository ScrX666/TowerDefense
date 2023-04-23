// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/TPlayerController.h"

#include "Building/TMainBuilding.h"


ATPlayerController::ATPlayerController() :
BuildingMode(EBuildingMode::E_NotInBuildMode), BuildingRefer(nullptr), CursorHitActor(nullptr)
{
	
}

void ATPlayerController::SetBuildingMode(TSubclassOf<ATMainBuilding> BuildingCla)
{
	this->BuildingClass = BuildingCla;
	if( BuildingMode == EBuildingMode::E_InBuildMode)
	{
		// 放下
		BuildingMode = EBuildingMode::E_NotInBuildMode;
		BuildingModeOff();
	}
	else
	{
		// 拿起
		BuildingMode = EBuildingMode::E_InBuildMode;
		BuildingModeOn();
	}
}

void ATPlayerController::MouseClickDown()
{

}

void ATPlayerController::MouseMove(float Value)
{

	FHitResult HitResult;
	GetHitResultUnderCursorByChannel(TraceTypeQuery1, true, HitResult);
	CursorLocation = HitResult.Location;
	if( CursorHitActor != HitResult.Actor)
	{
		if( CursorHitActor != nullptr)
		{
			CursorHitActor->OnHovered(false);
		}
		CursorHitActor = Cast<ATMainBuilding>(HitResult.Actor);
		if( CursorHitActor)
			CursorHitActor->OnHovered(true);
	}
	
}

void ATPlayerController::BeginPlay()
{
	Super::BeginPlay();

	this->SetShowMouseCursor(true);
}

void ATPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("MouseClick"), IE_Pressed, this, &ATPlayerController::MouseClickDown);
	InputComponent->BindAxis(TEXT("MouseMove"), this, &ATPlayerController::MouseMove);
}

void ATPlayerController::BuildingModeOff()
{
	if( BuildingRefer)
	{
		BuildingRefer->Destroy();
	}
}

void ATPlayerController::BuildingModeOn()
{
	BuildingRefer = GetWorld()->SpawnActor<ATMainBuilding>(BuildingClass, CursorLocation,FRotator::ZeroRotator);
	BuildingRefer->ToggleBuildingMode(BuildingMode == EBuildingMode::E_InBuildMode);
	if( BuildingRefer->Implements<UTBuildingInterface>())
	{
		BuildingRefer->OnConstruct(nullptr);
	}
}
