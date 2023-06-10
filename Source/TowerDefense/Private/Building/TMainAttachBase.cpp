// Fill out your copyright notice in the Description page of Project Settings.


#include "Building/TMainAttachBase.h"

#include "Building/TMainBuilding.h"
#include "Components/ArrowComponent.h"

// Sets default values
ATMainAttachBase::ATMainAttachBase():
	AttachedBuilding(nullptr)
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	AttachedBuildingPos = CreateDefaultSubobject<USceneComponent>(TEXT("BuildingPos"));
	RootComponent = Mesh;
	Arrow->SetupAttachment(Mesh);
	AttachedBuildingPos->SetupAttachment(RootComponent);

	Mesh->SetCollisionProfileName(TEXT("BuildingBase"));
}

void ATMainAttachBase::OnConstructAttachBuilding(ATMainBuilding* Building)
{
	this->AttachedBuilding = Building;
}

void ATMainAttachBase::OnSnapAttachBuilding()
{
	AttachedBuilding->Destroy();
}