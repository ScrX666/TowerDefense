// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/TBaseItem.h"

#include "Components/WidgetComponent.h"

// Sets default values
ATBaseItem::ATBaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthWidgetComp"));
	RootComponent = MeshComponent;
	WidgetComponent->SetupAttachment(RootComponent);
	WidgetComponent->SetVisibility(false);
}

void ATBaseItem::EnableItem(bool bActive)
{
	bIsItemActive = bActive;
	BlueprintEnableItem(bActive);
}

// Called when the game starts or when spawned
void ATBaseItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATBaseItem::Interact(APawn* InstigatorPawn)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red,TEXT("Interact"));
}

void ATBaseItem::ActiveTipsUI_Implementation(bool bIsActive)
{
	ITInteractInterface::ActiveTipsUI_Implementation(bIsActive);
	WidgetComponent->SetVisibility(bIsActive);
}

void ATBaseItem::Interact_Implementation(APawn* InstigatorPawn)
{
	ITInteractInterface::Interact_Implementation(InstigatorPawn);
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red,TEXT("Interact_Implementation"));
}

