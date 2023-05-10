// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Building/Tower/TMainTower.h"
#include "Structure/FTBeamTower.h"
#include "TMainBeamTower.generated.h"

class UTBeamTowerState;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATMainBeamTower : public ATMainTower
{
	GENERATED_BODY()
public:
	ATMainBeamTower();
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ATLaserBeam> BeamClass;
	UPROPERTY(EditAnywhere)
	FTBeamTower ShotTowerData;
	UPROPERTY()
	TArray<ATLaserBeam*> LaserBeams;
	UPROPERTY()
	TArray<ATLaserBeam*> LaserBeamBeUsed;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UTBeamTowerState* BeamTowerStateComp;
	
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

	virtual int32 GetCostCoins() override;

	
	UFUNCTION()
	void UpdateBeamDamage(float NewDamage);

	void SetLaserBeamsNum(const int32 NewCount);
	
private:
	virtual void Fire() override;
	virtual void OnDestory() override;

	virtual void TargetInRange() override;
	virtual void NoTargetInRange() override;
	virtual void GetExp(int Exp) override;
};
