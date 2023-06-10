// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TMainAttachBase.generated.h"

class ATMainBuilding;
class UArrowComponent;

UCLASS()
class TOWERDEFENSE_API ATMainAttachBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ATMainAttachBase();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere)
	UArrowComponent* Arrow;
	UPROPERTY(VisibleAnywhere)
	USceneComponent* AttachedBuildingPos;
	UPROPERTY(VisibleAnywhere)
	ATMainBuilding* AttachedBuilding;

public:	

	void OnConstructAttachBuilding(ATMainBuilding* Building);
	void OnSnapAttachBuilding();
	
};
