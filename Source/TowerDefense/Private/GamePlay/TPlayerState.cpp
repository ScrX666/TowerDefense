// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/TPlayerState.h"

#include "Building/TPathEndBuilding.h"
#include "Component/ActorComp/Tower/TTowerStateComponent.h"
#include "Kismet/GameplayStatics.h"

ATPlayerState::ATPlayerState()
	:Coins(100)
{
	AllEnemyDead = false;
}

void ATPlayerState::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> Out;
	UGameplayStatics::GetAllActorsOfClass(this,ATPathEndBuilding::StaticClass(),Out);
	if( Out.Num() > 0)
	EndBuilding = Cast<ATPathEndBuilding>(Out[0]);
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

bool ATPlayerState::PurchaseExp(int32 ExpNum,UTTowerStateComponent* TowerState)
{
	if( CoinsEnough(ExpNum) && TowerState->GetMaxLevel() > TowerState->GetCurrentLevel())
	{
		RemoveCoins(ExpNum);
		TowerState->GetExp(ExpNum);
		return true;
	}
	else
	{
		return false;
	}
}
