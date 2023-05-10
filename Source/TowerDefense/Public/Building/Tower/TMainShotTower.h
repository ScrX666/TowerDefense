// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Building/Tower/TMainTower.h"
#include "Structure/FTShotTower.h"
#include "TMainShotTower.generated.h"

class ATMainBullet;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATMainShotTower : public ATMainTower
{
	GENERATED_BODY()
public:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	class UTShotTowerState* ShotTowerStateComp;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ATMainBullet> BulletClass;

	
private:
	FTimerHandle FireTimerHandle;


public:
	
	ATMainShotTower();
	/*
	 * 继承接口
	 */
	virtual void OnConstruct(ATMainAttachBase* AttachBase) override;
	virtual void BeginPlay() override;


	/*
	 * UE 自带
	 */
	virtual void OnConstruction(const FTransform& Transform) override;
	void UpdateShotRate(float ShotRate);
	virtual int32 GetCostCoins() override;
	
private:
	virtual void Fire() override;
	virtual void OnDestory() override;

	virtual void TargetInRange() override;
	virtual void NoTargetInRange() override;
	virtual void GetExp(int Exp) override;
};
