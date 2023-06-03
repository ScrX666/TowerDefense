// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "TAssetManager.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnPackageLoaded);

/**
 * 弃用
 */
UCLASS()
class TOWERDEFENSE_API UTAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	FString CurrentLoadPackage;
public:
	UFUNCTION(BlueprintPure,CallInEditor,DisplayName = "AssetManager")
	static UTAssetManager* Get();
	UFUNCTION(BlueprintCallable,CallInEditor)
	FString AsynLoadObject(FSoftObjectPath Path,FOnPackageLoaded OnPackageLoaded);
	UFUNCTION(BlueprintCallable,CallInEditor)
	float GetCurrentLoadProgress(int32& LoadedCount,int32& RequestedCount) const;
};
