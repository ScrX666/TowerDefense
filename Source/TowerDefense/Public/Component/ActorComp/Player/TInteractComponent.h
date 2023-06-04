// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/TInteractInterface.h"
#include "TInteractComponent.generated.h"


class UCharacterMovementComponent;
class USphereComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UTInteractComponent : public UActorComponent
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	TArray<TScriptInterface<ITInteractInterface>> DetectedActors;
	
public:
	UTInteractComponent();

	void PrimaryInteract();
	UFUNCTION()
	void OnEnterDetectRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnExitDetectRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
