// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TManBase.h"
#include "Interface/TBuildingInterface.h"
#include "TSoldierBase.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATSoldierBase : public ATManBase, public ITBuildingInterface
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	TMap<FName, UMaterialInterface*> Materials;
	
public:
	ATSoldierBase();
	virtual void OnConstruct(ATMainAttachBase* AttachBase) override;
	virtual void OnDestory() override;
	virtual void OnHovered(bool bHovered) override;
	virtual void OnSelected(bool bIsSelected) override;
	virtual void CanConstructBuilding(bool bCanConstruct) override;
	virtual int32 GetCostCoins() override;
private:
	virtual void ChangeMaterial(FName MatName);
};
