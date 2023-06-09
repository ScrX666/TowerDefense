// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ActorComp/Tower/TTowerStateComponent.h"

#include "Kismet/KismetArrayLibrary.h"

// Sets default values for this component's properties
UTTowerStateComponent::UTTowerStateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

const TArray<FTTowerAbility>& UTTowerStateComponent::GetAllAbility() const
{
	return TowerAbilities;
}

void UTTowerStateComponent::ApplyAbility(const FTTowerAbility& TowerAbility, int32 Index)
{
	SelectedAbilityIndex = Index;
}

int32 UTTowerStateComponent::GetMaxLevel() const
{
	return 0;
}

int32 UTTowerStateComponent::GetCurrentLevel() const
{
	return 0;
}

void UTTowerStateComponent::GetExp(const int Exp)
{
}


// Called when the game starts
void UTTowerStateComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

