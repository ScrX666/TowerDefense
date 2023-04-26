// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	ATPlayerState();
	
private:
	UPROPERTY(EditDefaultsOnly)
	int Coins;
public:
	void RemoveCoins(int RemoveCoin);
	void AddCoins(int AddCoin);
	/*
	 * 判断金币是否足够
	 */
	bool CoinsEnough(int DesireCoin) const;

	UFUNCTION(BlueprintCallable)
	int GetCoins() const ;
};
