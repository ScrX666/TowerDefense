// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/TDataTableManager.h"

#include "Kismet/GameplayStatics.h"
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

FTBeamTower TDataTableManager::GetBeamTowerData(FName Name)
{
	if( BeamTowerTable == nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("BeamTowerTable NULL"));
		return FTBeamTower();
	}
	const FString ContextStr;
	auto Res = BeamTowerTable->FindRow<FTBeamTower>(Name,ContextStr);
	if( Res == nullptr)
	{
		return FTBeamTower();
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

FAISpawnStruct TDataTableManager::GetAISpawnStruct(FName Name)
{
	if( AISpawnTable == nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("AISpawnTable NULL"));
		return FAISpawnStruct();
	}
	const FString ContextStr;
	auto Res = AISpawnTable->FindRow<FAISpawnStruct>(Name,ContextStr);
	if( Res == nullptr)
	{
		return FAISpawnStruct();
	}
	return *Res;
}

FAISpawnStruct TDataTableManager::GetAISpawnStruct(int RowIndex)
{
	if( AISpawnTable == nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("AISpawnTable NULL"));
		return FAISpawnStruct();
	}
	const FString ContextStr;
	// static TArray<FAISpawnStruct*> OutArray; 打包时使用
	TArray<FAISpawnStruct*> OutArray;
	if( OutArray.Num() == 0)
	{
		AISpawnTable->GetAllRows<FAISpawnStruct>(ContextStr,OutArray);
		AISpawnTableLength = OutArray.Num();
	}
	if( RowIndex > OutArray.Num() - 1)
	{
		UE_LOG(LogTemp,Warning,TEXT("AISpawnTable Index Out Of Range"));
		return FAISpawnStruct();
	}
	
	auto Res = OutArray[RowIndex];
	if( Res == nullptr)
	{
		return FAISpawnStruct();
	}
	return *Res;
}

FName TDataTableManager::GetNextLevel( const FName CurrentLevelName)
{
	if( LevelInfoTable == nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("LevelInfoTable NULL"));
		return FName();
	}
	const FString ContextStr;
	// static TArray<FAISpawnStruct*> OutArray; 打包时使用
	TArray<FTLevelInfo*> OutArray;
	if( OutArray.Num() == 0)
	{
		LevelInfoTable->GetAllRows<FTLevelInfo>(ContextStr,OutArray);
	}
	for( int i = 0; i < OutArray.Num(); i++)
	{
		if( OutArray[i]->Level)
		{
			UE_LOG(LogTemp,Log,TEXT("Level Name %s"),*OutArray[i]->Level->GetName());
		}
		
		if( OutArray[i]->Level && FName(OutArray[i]->Level->GetName()) == CurrentLevelName)
		{
			if( i < OutArray.Num() - 1 && OutArray[i + 1]->Level)
			{
				return FName(OutArray[i + 1]->Level->GetName());
			}
			else
			{
				return FName();
			}
		}
			
	}
	return FName();
}

TArray<TSubclassOf<ATMainTower>> TDataTableManager::GetWinTowers(const FName CurrentLevelName)
{
	if( LevelInfoTable == nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("LevelInfoTable NULL"));
		return TArray<TSubclassOf<ATMainTower>>();
	}
	const FString ContextStr;
	// static TArray<FAISpawnStruct*> OutArray; 打包时使用
	TArray<FTLevelInfo*> OutArray;
	if( OutArray.Num() == 0)
	{
		LevelInfoTable->GetAllRows<FTLevelInfo>(ContextStr,OutArray);
	}
	TArray<TSubclassOf<ATMainTower>> ResTowers;
	for( int i = 0; i < OutArray.Num(); i++)
	{
		if( OutArray[i]->Level)
		{
			UE_LOG(LogTemp,Log,TEXT("Level Name %s"),*OutArray[i]->Level->GetName());
		}
		
		if( OutArray[i]->Level && FName(OutArray[i]->Level->GetName()) == CurrentLevelName)
		{
			for( const TSubclassOf<ATMainTower>& Tower : OutArray[i]->WinTowers)
			{
				ResTowers.Add(Tower);
			}
		}
			
	}
	return ResTowers;
}

int32 TDataTableManager::GetLevelInitCoins(const FName CurrentLevelName)
{
	if( LevelInfoTable == nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("LevelInfoTable NULL"));
		return 100;
	}
	const FString ContextStr;
	// static TArray<FAISpawnStruct*> OutArray; 打包时使用
	TArray<FTLevelInfo*> OutArray;
	if( OutArray.Num() == 0)
	{
		LevelInfoTable->GetAllRows<FTLevelInfo>(ContextStr,OutArray);
	}
	int32 ResCoins = 100;
	for( int i = 0; i < OutArray.Num(); i++)
	{
		if( OutArray[i]->Level)
		{
			UE_LOG(LogTemp,Log,TEXT("Level Name %s"),*OutArray[i]->Level->GetName());
		}
		
		if( OutArray[i]->Level && FName(OutArray[i]->Level->GetName()) == CurrentLevelName)
		{
			ResCoins = OutArray[i]->InitCoins;
		}
			
	}
	return ResCoins;
}

int TDataTableManager::GetAISpawnStructNum()
{
	if(AISpawnTableLength == 0)
		GetAISpawnStruct(0);
	return AISpawnTableLength;
}

TDataTableManager::TDataTableManager()
{
	ShotTowerTable = LoadObject<UDataTable>(nullptr, UTF8_TO_TCHAR("/Game/BluePrint/Table/T_ShotTower"));
	BeamTowerTable = LoadObject<UDataTable>(nullptr, UTF8_TO_TCHAR("/Game/BluePrint/Table/T_BeamTower"));
	TowerTable = LoadObject<UDataTable>(nullptr, UTF8_TO_TCHAR("/Game/BluePrint/Table/T_Tower"));
	ManStateTable = LoadObject<UDataTable>(nullptr, UTF8_TO_TCHAR("/Game/BluePrint/Table/T_ManState"));
	AISpawnTable = LoadObject<UDataTable>(nullptr, UTF8_TO_TCHAR("/Game/BluePrint/Table/T_AISpawn"));
	LevelInfoTable = LoadObject<UDataTable>(nullptr, UTF8_TO_TCHAR("/Game/BluePrint/Table/T_LevelInfo"));
	AISpawnTableLength = 0;
	// TODO: 测试是否多次构造
	UE_LOG(LogTemp, Log,TEXT("Construct DataTableManager"));
}

TDataTableManager::~TDataTableManager()
{

}
