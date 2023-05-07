// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <mutex>

#include "CoreMinimal.h"
#include "Structure/FAISpawnStruct.h"
#include "Structure/FTBeamTower.h"
#include "Structure/FTManState.h"
#include "Structure/FTTower.h"

class UDataTable;
struct FTShotTower;

// 加锁的懒汉式实现

class TOWERDEFENSE_API TDataTableManager
{

public:
	// 获取单实例对象
	static TDataTableManager *GetInstance();

	// //释放单实例，进程退出时调用
	// static void deleteInstance();
	
private:
	UDataTable* ShotTowerTable;
	UDataTable* BeamTowerTable;
	UDataTable* TowerTable;
	UDataTable* ManStateTable;
	UDataTable* AISpawnTable;
	int AISpawnTableLength;
public:
	/*
	 * 获取射击塔的信息
	 */
	FTShotTower GetShotTowerData(FName Name);
	/*
	 * 获取激光塔的信息
	 */
	FTBeamTower GetBeamTowerData(FName Name);
	/*
	 * 获取塔的信息
	 */
	FTTower GetTowerData(FName Name);
	/*
	 * 获取人物信息
	 */
	FTManState GetManStateData(FName Name);

	/*
	 * 根据Name 获取
	 */
	FAISpawnStruct GetAISpawnStruct(FName Name);

	/*
	 * 根据index 获取
	 */
	FAISpawnStruct GetAISpawnStruct(int RowIndex);

	int GetAISpawnStructNum();
	
	
private:
	// 将其构造和析构成为私有的, 禁止外部构造和析构
	TDataTableManager();
	~TDataTableManager();

	// 将其拷贝构造和赋值构造成为私有函数, 禁止外部拷贝和赋值
	TDataTableManager(const TDataTableManager &signal) = delete;
	const TDataTableManager &operator=(const TDataTableManager &signal) = delete;

private:
	// 唯一单实例对象指针
	static TDataTableManager *DataTableManager;
	static std::mutex Mutex;
};
