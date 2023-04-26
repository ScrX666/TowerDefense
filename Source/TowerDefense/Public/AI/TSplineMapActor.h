// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "TSplineMapActor.generated.h"

UCLASS()
class TOWERDEFENSE_API ATSplineMapActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATSplineMapActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void AddArrow();
	UFUNCTION()
	void AIMove(ATFirstAIController* NPC);
	UFUNCTION()
	void SpawnAI();

	
protected:
	UPROPERTY(VisibleAnywhere)
	USplineComponent* SplineComponent;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> BP_AICharacter;
	FVector FirstMoveLoc;
public:
	UFUNCTION()
	void MoveTo(ATFirstAIController* AIController, int index, FVector& NextPosition);
	
};
