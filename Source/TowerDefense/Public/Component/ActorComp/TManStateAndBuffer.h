// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structure/FTManState.h"
#include "TManStateAndBuffer.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, UTManStateAndBuffer*, OwningComp, float, NewHealth, float, Delta);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDead, AActor*, InstigatorActor);
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
	float CurrentHealth;
	// TODO: 添加Buffer
protected:
	UFUNCTION()
	void DestorySelf(AActor* InstigatorActor);
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void ApplyHealthChange(AActor* Instigator, float Delta);

	UFUNCTION()
	void AddCoinsAndExp(AActor* InstigatorActor);

	UPROPERTY(BlueprintAssignable,BlueprintReadOnly)
	FOnHealthChanged OnHealthChanged;
	UPROPERTY(BlueprintAssignable,BlueprintReadOnly)
	FOnDead OnDead;
};
