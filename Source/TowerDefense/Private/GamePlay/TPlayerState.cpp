// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/TPlayerState.h"

ATPlayerState::ATPlayerState()
	:Coins(100)
{
}

void ATPlayerState::RemoveCoins(int RemoveCoin)
{
	Coins -= RemoveCoin;
	OnCoinChanged.Broadcast(Coins,-RemoveCoin);
}

void ATPlayerState::AddCoins(int AddCoin)
{
	Coins += AddCoin;
	OnCoinChanged.Broadcast(Coins,AddCoin);
}

bool ATPlayerState::CoinsEnough(int DesireCoin) const
{
	return DesireCoin <= Coins;
}

int ATPlayerState::GetCoins() const
{
	return Coins;
}
