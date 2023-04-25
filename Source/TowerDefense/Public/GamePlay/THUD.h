// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "THUD.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATHUD : public AHUD
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> TowerDefenseClass;

	UPROPERTY(VisibleAnywhere)
	UUserWidget* TowerDefense;
	
	virtual void BeginPlay() override;
};
