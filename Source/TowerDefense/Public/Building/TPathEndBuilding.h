// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Building/TMainBuilding.h"
#include "Component/ActorComp/TManStateAndBuffer.h"
#include "TPathEndBuilding.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHomeHealthChanged, float, NewHealth, float, Delta);
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
	UPROPERTY(BlueprintAssignable,BlueprintReadOnly)
	FOnHomeHealthChanged OnHomeHealthChanged;
	
private:
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* SphereComponent;

	UFUNCTION()
	void RangeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void RangeOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	bool IsDead();
};
