// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TowerDefenseGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameEnd, bool,IsWin);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameReallyStart);
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATowerDefenseGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	ATowerDefenseGameModeBase();

public:
	int LevelIndex = 0;
	bool bGameEnd = false;
	UPROPERTY(BlueprintAssignable,EditAnywhere)
	FOnGameEnd OnGameEnd;
	UPROPERTY(BlueprintAssignable,EditAnywhere)
	FOnGameReallyStart OnGameStart;
public:
	UFUNCTION()
	void GameEnd(bool IsWin);
	UFUNCTION(BlueprintCallable)
	void GameStart();
protected:
	virtual void BeginPlay() override;
};
