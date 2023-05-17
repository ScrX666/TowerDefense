// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enum/EBuildingMode.h"
#include "UObject/Interface.h"
#include "TBuildingInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTBuildingInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */

class ATMainAttachBase;

class TOWERDEFENSE_API ITBuildingInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void OnConstruct(ATMainAttachBase* AttachBase) = 0;
	virtual void OnDestory() = 0;
	virtual void OnHovered(bool bHovered) = 0;
	virtual void OnSelected(bool bIsSelected) = 0;
	virtual void CanConstructBuilding(bool bCanConstruct) = 0;
	virtual int32 GetCostCoins() = 0;
};
