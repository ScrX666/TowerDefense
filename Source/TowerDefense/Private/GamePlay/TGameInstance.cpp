// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/TGameInstance.h"


bool UTGameInstance::AddTower(TSubclassOf<ATMainTower> Tower)
{
	if( OwnTowers.Contains(Tower)) return false;
	OwnTowers.Add(Tower);
	return true;
}

const TArray<TSubclassOf<ATMainTower>>& UTGameInstance::GetOwnTowers()
{
	if( OwnTowers.Num() == 0)
	{
		for( TSubclassOf<ATMainTower>& Tower : InitTowers)
		{
			OwnTowers.AddUnique(Tower);
		}
	}
	return OwnTowers;
}
