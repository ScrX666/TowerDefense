// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TBaseSkill.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCoolDownUpdate,float,CurrentCoolDown,float,SkillCoolDown,bool,bCanUse);
/**
 * 基础技能
 */
UCLASS(BlueprintType, Abstract)
class TOWERDEFENSE_API UTBaseSkill : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	bool bCanUse = true;
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	float SkillCoolDown = 2.0f;
	UPROPERTY(BlueprintReadOnly)
	float CurrentCoolDown;
	UPROPERTY(BlueprintAssignable,BlueprintReadOnly)
	FOnCoolDownUpdate OnCDUpdate;

	FTimerHandle CoolDownHandle; // 更新技能的TimerHandle
protected:
	UPROPERTY()
	UWorld* CurWorld;
public:
	/*
	 * 释放技能
	 */
	virtual void Execute(UWorld* World);
	/*
	 * 技能的相关初始化
	 */
	virtual void Init(UWorld* World);
protected:
	/*
	 * 更新技能状态 定时调用
	 */
	UFUNCTION()
	virtual void OnCoolDownUpdate();
};
