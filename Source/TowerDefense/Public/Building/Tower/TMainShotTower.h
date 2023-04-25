// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Building/Tower/TMainTower.h"
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
	

private:
	FTimerHandle FireTimerHandle;


public:
	virtual void OnConstruct(ATMainAttachBase* AttachBase) override;
	virtual void BeginPlay() override;
private:
	virtual void Fire() override;
	virtual void OnDestory() override;
};
