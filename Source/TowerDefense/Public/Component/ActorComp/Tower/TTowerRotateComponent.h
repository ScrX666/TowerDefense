// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TTowerRotateComponent.generated.h"


class ATMainTower;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UTTowerRotateComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	float RotateSpeed;
	
private:
	// UPROPERTY(EditDefaultsOnly)
	// bool bUseRootAsRotate;
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* RotateComponent;
	UPROPERTY()
	ATMainTower* Tower;

public:
	UTTowerRotateComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
		
};
