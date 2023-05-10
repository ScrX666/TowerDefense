// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TShotTowerState.h"
#include "Components/ActorComponent.h"
#include "Structure/FTBeamTower.h"
#include "Structure/FTTowerAbility.h"
#include "Tower/TTowerStateComponent.h"
#include "TBeamTowerState.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeamTowerGetExp,UTBeamTowerState*,BeamTowerStateComp);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UTBeamTowerState : public UTTowerStateComponent
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
	UFUNCTION(BlueprintPure)
	const TArray<FTManBuffer>& GetApplyBuffers() const;
	// UFUNCTION(BlueprintCallable)
	virtual void ApplyAbility(const FTTowerAbility& TowerAbility) override;
	/*
	 * 获取所有可加点能力
	 */
	// UFUNCTION(BlueprintCallable)
	virtual const TArray<FTTowerAbility>& GetAllAbility() const override;
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
	
	// 更新状态
	UFUNCTION()
	void UpdateParallelAttackCount(const int32 NewCount);
	
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
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	int32 ParallelAttackCount;
	
private:
	
	UPROPERTY(EditAnywhere)
	FTBeamTower BeamTowerData;
	UPROPERTY()
	ATMainTower* Tower;
};
