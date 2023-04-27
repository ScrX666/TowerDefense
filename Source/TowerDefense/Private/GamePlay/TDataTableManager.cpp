// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/TDataTableManager.h"

#include "Structure/FTShotTower.h"
#include "Structure/FTTower.h"


//初始化静态成员变量
TDataTableManager *TDataTableManager::DataTableManager = nullptr;
std::mutex TDataTableManager::Mutex;

// 不能返回指针的引用，否则存在外部被修改
TDataTableManager* TDataTableManager::GetInstance()
{
	if (DataTableManager == nullptr) 
	{
		std::unique_lock<std::mutex> lock(Mutex); // 加锁
		if (DataTableManager == nullptr)
		{
			auto temp = new (std::nothrow) TDataTableManager();
			DataTableManager = temp;
		}
	}

	return DataTableManager;
}


FTShotTower TDataTableManager::GetShotTowerData(FName Name)
{
	if( ShotTowerTable == nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("ShotTowerTable NULL"));
		return FTShotTower();
	}
	const FString ContextStr;
	auto Res = ShotTowerTable->FindRow<FTShotTower>(Name,ContextStr);
	if( Res == nullptr)
	{
		return FTShotTower();
	}
	return *Res;
}

FTTower TDataTableManager::GetTowerData(FName Name)
{
	if( TowerTable == nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("TowerTable NULL"));
		return FTTower();
	}
	const FString ContextStr;
	auto Res = TowerTable->FindRow<FTTower>(Name,ContextStr);
	if( Res == nullptr)
	{
		return FTTower();
	}
	return *Res;
}

FTManState TDataTableManager::GetManStateData(FName Name)
{
	if( ManStateTable == nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("ManStateTable NULL"));
		return FTManState();
	}
	const FString ContextStr;
	auto Res = ManStateTable->FindRow<FTManState>(Name,ContextStr);
	if( Res == nullptr)
	{
		return FTManState();
	}
	return *Res;
}

TDataTableManager::TDataTableManager()
{
	ShotTowerTable = LoadObject<UDataTable>(nullptr, UTF8_TO_TCHAR("/Game/BluePrint/Table/T_ShotTower"));
	TowerTable = LoadObject<UDataTable>(nullptr, UTF8_TO_TCHAR("/Game/BluePrint/Table/T_Tower"));
	ManStateTable = LoadObject<UDataTable>(nullptr, UTF8_TO_TCHAR("/Game/BluePrint/Table/T_ManState"));
	// TODO: 测试是否多次构造
	UE_LOG(LogTemp, Log,TEXT("Construct DataTableManager"));
}

TDataTableManager::~TDataTableManager()
{

}
