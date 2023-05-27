// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Building/Tower/TMainTower.h"
#include "Engine/GameInstance.h"
#include "TGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<ATMainTower>> InitTowers; // 初始时拥有的塔
	UPROPERTY(BlueprintReadOnly)
	float MusicVolume = 1.0f;
	UPROPERTY(BlueprintReadOnly)
	float SoundVolume = 1.0f;
private:
	UPROPERTY(VisibleAnywhere)
	TArray<TSubclassOf<ATMainTower>> OwnTowers; // 拥有的塔
public:
	UFUNCTION(BlueprintCallable)
	bool AddTower(TSubclassOf<ATMainTower> Tower);
	UFUNCTION(BlueprintCallable)
	const TArray<TSubclassOf<ATMainTower>>& GetOwnTowers();
};
