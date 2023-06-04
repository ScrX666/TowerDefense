// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TBaseLocationSkill.h"
#include "Character/TSoldierBase.h"
#include "Skill/TBaseSkill.h"
#include "TSpawnSoliderSkill.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TOWERDEFENSE_API UTSpawnSoliderSkill : public UTBaseLocationSkill
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATSoldierBase> SoliderCla;
	UPROPERTY(EditDefaultsOnly)
	int32 SpawnCount;
	UPROPERTY(EditDefaultsOnly)
	float RandomRange = 50.0f;
private:
	float SoliderScale = 1.0f; // 士兵的缩放
public:
	/*
	 * 技能实际执行函数
	 */
	virtual void Execute(UWorld* World) override;
	/*
	 * 技能初始化
	 */
	virtual void Init(UWorld* World) override;
};
