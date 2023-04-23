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
	// Sets default values for this actor's properties
	ATMainAttachBase();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere)
	UArrowComponent* Arrow;
	
protected:
	// Called when the game starts or when spawned

	virtual void BeginPlay() override;

	ATMainBuilding* AttachedBuilding;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnConstructAttachBuilding(ATMainBuilding* Building);
	void OnSnapAttachBuilding();
	
};
