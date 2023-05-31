// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/TBaseItem.h"

#include "Components/WidgetComponent.h"

// Sets default values
ATBaseItem::ATBaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthWidgetComp"));
	RootComponent = MeshComponent;
	HealthWidgetComponent->SetupAttachment(RootComponent);
	HealthWidgetComponent->SetVisibility(false);
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

void ATBaseItem::Interact(APawn* InstigatorPawn)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red,TEXT("Interact"));
}

void ATBaseItem::ActiveTipsUI_Implementation(bool bIsActive)
{
	ITInteractInterface::ActiveTipsUI_Implementation(bIsActive);
	HealthWidgetComponent->SetVisibility(bIsActive);
}

void ATBaseItem::Interact_Implementation(APawn* InstigatorPawn)
{
	ITInteractInterface::Interact_Implementation(InstigatorPawn);
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red,TEXT("Interact"));
}

