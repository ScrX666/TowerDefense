// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TAICharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ATAICharacter::ATAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}

// Called when the game starts or when spawned
void ATAICharacter::BeginPlay()
{
	Super::BeginPlay();
}
void ATAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


