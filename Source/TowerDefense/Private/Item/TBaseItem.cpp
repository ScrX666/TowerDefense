// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/TBaseItem.h"

// Sets default values
ATBaseItem::ATBaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
}

// Called when the game starts or when spawned
void ATBaseItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATBaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATBaseItem::Interact_Implementation(APawn* InstigatorPawn)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red,TEXT("Interact"));
}

