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
	ATMainShotTower();
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ATMainBullet> BulletClass;
	UPROPERTY(EditAnywhere)
	FTShotTower ShotTowerData;
	
private:
	FTimerHandle FireTimerHandle;


public:
	/*
	 * 继承接口
	 */
	virtual void OnConstruct(ATMainAttachBase* AttachBase) override;
	virtual void BeginPlay() override;


	/*
	 * UE 自带
	 */
	virtual void OnConstruction(const FTransform& Transform) override;
	
private:
	virtual void Fire() override;
	virtual void OnDestory() override;
};
