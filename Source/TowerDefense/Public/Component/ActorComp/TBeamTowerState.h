// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TShotTowerState.h"
#include "Components/ActorComponent.h"
#include "Structure/FTBeamTower.h"
#include "TBeamTowerState.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeamTowerGetExp,UTBeamTowerState*,BeamTowerStateComp);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UTBeamTowerState : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTBeamTowerState();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/*
	 * 初始化
	 */
	void Init(const FName Name);
	void GetExp(const int Exp);
	USoundBase* GetSoundClass() const;

	UFUNCTION(BlueprintPure)
	int32 GetLevelUpExp() const;
	UFUNCTION(BlueprintPure)
	int32 GetCostCoins() const;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
private:
	// 更新状态
	UFUNCTION()
	void UpdateLevel(const int32 NewLevel);
	UFUNCTION()
	void UpdateDamage(const int32 NewLevel);
	UFUNCTION()
	void UpdateAttackRange(const int32 NewLevel);

public:
	UPROPERTY(VisibleAnywhere,BlueprintAssignable)
	FOnLevelUp OnLevelUp;
	UPROPERTY(VisibleAnywhere,BlueprintAssignable)
	FOnBeamTowerGetExp OnGetExp;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	int32 CurrentLevel = 0;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	int32 CurrentExp = 0;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	float CurrentDamage;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	float CurrentAttackRange;
	
private:
	
	UPROPERTY(EditAnywhere)
	FTBeamTower BeamTowerData;
		
};