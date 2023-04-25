// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/THUD.h"


#include "Blueprint/UserWidget.h"

void ATHUD::BeginPlay()
{
	Super::BeginPlay();
	TowerDefense = CreateWidget(GetWorld(), TowerDefenseClass);
	TowerDefense->AddToViewport();
}
