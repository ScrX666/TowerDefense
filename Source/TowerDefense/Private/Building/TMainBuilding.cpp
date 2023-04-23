// Fill out your copyright notice in the Description page of Project Settings.


#include "Building/TMainBuilding.h"

// Sets default values
ATMainBuilding::ATMainBuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
	
}

// Called when the game starts or when spawned
void ATMainBuilding::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATMainBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATMainBuilding::OnConstruct(ATMainAttachBase* AttachBase)
{
}

void ATMainBuilding::OnDestory()
{
}

void ATMainBuilding::OnHovered(bool bHovered)
{
	UE_LOG(LogTemp, Log, TEXT("Hover"));
	// int i = 0;
	// if( bHovered)
	// {
	// 	i = 1;
	// }
	// else
	// 	i = 2;
	// UE_LOG(LogTemp, Log,TEXT("%d"), i);
	
}

void ATMainBuilding::ToggleBuildingMode(bool bBuildingMode)
{
}

