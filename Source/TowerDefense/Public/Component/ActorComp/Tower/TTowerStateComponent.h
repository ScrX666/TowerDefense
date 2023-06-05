// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structure/FTTowerAbility.h"
#include "Components/ActorComponent.h"
#include "TTowerStateComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTowerGetExp,UTTowerStateComponent*,ShotTowerStateComp);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UTTowerStateComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere,BlueprintAssignable)
	FOnTowerGetExp OnGetExp;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	int32 SelectedAbilityIndex = -1;
public:	
	// Sets default values for this component's properties
	UTTowerStateComponent();
	UFUNCTION(BlueprintCallable)
	virtual const TArray<FTTowerAbility>& GetAllAbility() const;
	UFUNCTION(BlueprintCallable)
	virtual void ApplyAbility(const FTTowerAbility& TowerAbility, int32 Index);
	UFUNCTION(BlueprintCallable)
	virtual  int32 GetMaxLevel() const;
	UFUNCTION(BlueprintCallable)
	virtual  int32 GetCurrentLevel() const;
	UFUNCTION(BlueprintCallable)
	virtual void GetExp(const int Exp);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
private:
	// 做本类 GetAllAbility的返回值
	TArray<FTTowerAbility> TowerAbilities;
};
