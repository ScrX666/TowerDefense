// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TGameInstance.generated.h"

class ATMainTower;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	TArray<ATMainTower*> InitTowers; // 初始时拥有的塔
private:
	UPROPERTY(EditDefaultsOnly)
	TArray<ATMainTower*> OwnTowers; // 初始时拥有的塔
};
