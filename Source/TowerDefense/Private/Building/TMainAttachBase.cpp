// Fill out your copyright notice in the Description page of Project Settings.


#include "Building/TMainAttachBase.h"

#include "Building/TMainBuilding.h"
#include "Components/ArrowComponent.h"

// Sets default values
ATMainAttachBase::ATMainAttachBase():
	AttachedBuilding(nullptr)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	AttachedBuildingPos = CreateDefaultSubobject<USceneComponent>(TEXT("BuildingPos"));
	RootComponent = Mesh;
	Arrow->SetupAttachment(Mesh);
	AttachedBuildingPos->SetupAttachment(RootComponent);

	Mesh->SetCollisionProfileName(TEXT("BuildingBase"));
}

// Called when the game starts or when spawned
void ATMainAttachBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATMainAttachBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATMainAttachBase::OnConstructAttachBuilding(ATMainBuilding* Building)
{
	this->AttachedBuilding = Building;
}

void ATMainAttachBase::OnSnapAttachBuilding()
{
	AttachedBuilding->Destroy();
}