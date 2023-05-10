// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structure/FTTowerAbility.h"
#include "Components/ActorComponent.h"
#include "TTowerStateComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UTTowerStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTTowerStateComponent();
	UFUNCTION(BlueprintCallable)
	virtual const TArray<FTTowerAbility>& GetAllAbility() const;
	UFUNCTION(BlueprintCallable)
	virtual void ApplyAbility(const FTTowerAbility& TowerAbility);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
private:
	// 做本类 GetAllAbility的返回值
	TArray<FTTowerAbility> TowerAbilities;
};
