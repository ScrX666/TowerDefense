// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TManBase.generated.h"

class UWidgetComponent;
class UTManStateAndBuffer;

UCLASS()
class TOWERDEFENSE_API ATManBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATManBase();
	UPROPERTY(EditDefaultsOnly)
	FName Name;
	UPROPERTY(VisibleAnywhere)
	UTManStateAndBuffer* ManStateAndBuffer;
	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* HealthWidgetComponent;
	UPROPERTY(VisibleAnywhere)
	TSubclassOf<UUserWidget> HealthBarWidget;

	
protected:
	UFUNCTION()
	void UpdateHealthBar(AActor* InstigatorActor, UTManStateAndBuffer* OwningComp, float NewHealth, float Delta);
	UFUNCTION()
	void DestorySelf();
	UFUNCTION()
	void AddCoins();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable,BlueprintPure)
	int GetMaxHealth();
	UFUNCTION(BlueprintCallable,BlueprintPure)
	int GetCurrentHealth();

private:

	/*
	 * 更新UI朝向
	 */
	void UpdateHealthBarRotation();
};
