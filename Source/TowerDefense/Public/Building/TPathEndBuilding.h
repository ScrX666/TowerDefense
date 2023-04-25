// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Building/TMainBuilding.h"
#include "TPathEndBuilding.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATPathEndBuilding : public ATMainBuilding
{
	GENERATED_BODY()
public:
	ATPathEndBuilding();

	UPROPERTY(BlueprintReadOnly)
	float MaxHealth;
	UPROPERTY(BlueprintReadOnly)
	float Health;
	
private:
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* SphereComponent;

	UFUNCTION()
	void RangeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void RangeOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void BeginPlay() override;
};
