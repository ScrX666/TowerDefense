// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TPlayerState.generated.h"
class UTTowerStateComponent;
class ATPathEndBuilding;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCoinChanged, float, NewHealth, float, Delta);
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	ATPlayerState();

	UPROPERTY(BlueprintAssignable,BlueprintReadOnly)
	FOnCoinChanged OnCoinChanged;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	ATPathEndBuilding* EndBuilding;

	bool AllEnemyDead;
	
private:
	UPROPERTY(EditDefaultsOnly)
	int Coins;
public:
	virtual void BeginPlay() override;
	
	void RemoveCoins(int RemoveCoin);
	void AddCoins(int AddCoin);
	/*
	 * 判断金币是否足够
	 */
	bool CoinsEnough(int DesireCoin) const;

	UFUNCTION(BlueprintCallable)
	int GetCoins() const ;
	UFUNCTION(BlueprintCallable)
	bool PurchaseExp(int32 ExpNum,UTTowerStateComponent* TowerState);
};
