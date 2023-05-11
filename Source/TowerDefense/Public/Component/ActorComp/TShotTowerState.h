// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structure/FTShotTower.h"
#include "Structure/FTTowerAbility.h"
#include "Tower/TTowerStateComponent.h"
#include "TShotTowerState.generated.h"

class ATMainTower;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUp,int32,NewLevel);
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShotTowerGetExp,UTShotTowerState*,ShotTowerStateComp);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UTShotTowerState : public UTTowerStateComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTShotTowerState();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/*
	 * 初始化
	 */
	void Init(const FName Name);
	virtual void GetExp(const int Exp) override;
	TSubclassOf<ATMainBullet> GetBulletClass() const;
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
	virtual int32 GetMaxLevel() const override;
	virtual int32 GetCurrentLevel() const override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
private:
	// 更新状态 升级时调用
	UFUNCTION()
	void UpdateLevel(const int32 NewLevel);
	UFUNCTION()
	void UpdateDamage(const int32 NewLevel);
	UFUNCTION()
	void UpdateAttackRange(const int32 NewLevel);
	UFUNCTION()
	void UpdateBulletSpeed(const int32 NewLevel);
	UFUNCTION()
	void UpdateShotRate(const int32 NewLevel);

	// 更新状态
	UFUNCTION()
	void UpdateParallelAttackCount(const int32 NewCount);
	
public:
	UPROPERTY(VisibleAnywhere,BlueprintAssignable)
	FOnLevelUp OnLevelUp;
	// UPROPERTY(VisibleAnywhere,BlueprintAssignable)
	// FOnShotTowerGetExp OnGetExp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	int32 CurrentLevel = 0;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	int32 CurrentExp = 0;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	float CurrentDamage;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	float CurrentAttackRange;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	float BulletSpeed;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	float ShotRate;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	int32 ParallelAttackCount;
	
	
private:
	
	UPROPERTY(EditAnywhere)
	FTShotTower ShotTowerData;
	UPROPERTY()
	ATMainTower* Tower;
};
