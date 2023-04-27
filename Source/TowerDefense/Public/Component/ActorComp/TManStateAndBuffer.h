// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structure/FTManState.h"
#include "TManStateAndBuffer.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, UTManStateAndBuffer*, OwningComp, float, NewHealth, float, Delta);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDead);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UTManStateAndBuffer : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTManStateAndBuffer();
	UPROPERTY(VisibleAnywhere)
	FTManState ManState;
	UPROPERTY(VisibleAnywhere)
	int CurrentHealth;
	// TODO: 添加Buffer
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void ApplyHealthChange(AActor* Instigator, int Delta);

	UPROPERTY(BlueprintAssignable,BlueprintReadOnly)
	FOnHealthChanged OnHealthChanged;
	UPROPERTY(BlueprintAssignable,BlueprintReadOnly)
	FOnDead OnDead;
};
