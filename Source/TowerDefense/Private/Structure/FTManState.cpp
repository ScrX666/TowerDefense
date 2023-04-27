// Fill out your copyright notice in the Description page of Project Settings.


#include "Structure/FTManState.h"

FTManState::FTManState()
{
	// static ConstructorHelpers::FObjectFinder<USkeletalMesh> DefaultSKMesh(TEXT("/Game/Mesh/Character/Default/TutorialTPP"));
	SkeletalMesh = nullptr;
	MaxHealth = 100;
	Coins = 10;
}