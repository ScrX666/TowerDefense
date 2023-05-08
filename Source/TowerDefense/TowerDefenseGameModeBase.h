// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TowerDefenseGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameEnd, bool,IsWin);
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATowerDefenseGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	ATowerDefenseGameModeBase();
protected:
	virtual void BeginPlay() override;

public:
	int LevelIndex = 0;
	bool bGameEnd = false;
	UPROPERTY(BlueprintAssignable,EditAnywhere)
	FOnGameEnd OnGameEnd;

	UFUNCTION()
	void GameEnd(bool IsWin);
};
