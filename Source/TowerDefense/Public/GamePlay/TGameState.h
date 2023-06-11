// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TGameState.generated.h"

class ATSplineMapActor;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	bool bIsWin;
private:
	UPROPERTY()
	TArray<ATSplineMapActor*> EnemySpawners;
	int32 CurrentExistEnemyCount = 0;
	
public:
	
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnEnemyNumChange(int32 Change);
private:
	bool IsFinishSpawn() const;
};
