// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TManBase.h"

// Sets default values
ATManBase::ATManBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATManBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATManBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATManBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

