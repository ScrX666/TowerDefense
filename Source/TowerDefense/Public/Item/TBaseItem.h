// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/TInteractInterface.h"
#include "TBaseItem.generated.h"

UCLASS()
class TOWERDEFENSE_API ATBaseItem : public AActor, public ITInteractInterface
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	ATBaseItem();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Interact_Implementation(APawn* InstigatorPawn);
};
