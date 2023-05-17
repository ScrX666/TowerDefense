// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Structure/FTBoolArray.h"
#include "TBlueprintFunctionLibrary.generated.h"


class ATMainTower;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable)
	static TArray<FTBoolArray> GetRandomPath(int32 Width, int32 Length, int32 N);
	UFUNCTION(BlueprintCallable)
	static FName GetNextLevel(const FName CurrentLevelName);
	UFUNCTION(BlueprintCallable)
	static int32 GetTowerCoinsByClassAndName(TSubclassOf<ATMainTower> Tower,FName Name);
};
