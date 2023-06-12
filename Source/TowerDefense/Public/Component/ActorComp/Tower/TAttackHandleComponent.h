// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <mutex>

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TAttackHandleComponent.generated.h"


class ATMainTower;
class ATManBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UTAttackHandleComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTAttackHandleComponent();
	/**
	 * @brief 进攻击范围，更新状态
	 * @param Man 近攻击范围的敌人
	 */
	void AttackTargetIn(ATManBase* Man);
	/**
	 * @brief 出攻击范围，更新状态
	 * @param Man 出攻击范围的敌人
	 */
	void AttackTargetOut(ATManBase* Man);
	
	/*
	 * 能够攻击的敌人数量是否已经满了
	 */
	bool TargetIsFull();
	/*
	 * 能够攻击的敌人数量是否为空
	 */
	bool TargetIsEmpty();
	/*
	 * 添加敌人
	 */
	bool AddTarget(ATManBase* ManBase);
	/*
	 * 设置并行攻击数量
	 */
	void SetParallelAttackCount(int32 NewCount);
	/*
	 * 获取并行攻击数量
	 */
	int32 GetParallelAttackCount() const;
	/*
	 * 获取攻击对象
	 */
	ATManBase* GetAttackTarget(int32 Index);
	/*
	 * 移除攻击对象
	 */
	void RemoveAttackTarget(const ATManBase* RemoveMan);	/*
	 * 移除攻击对象
	 */
	bool ExistInAttackTarget(const ATManBase* TargetMan) const;

	FVector ReturnTargetLocation() const;
	
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY()
	TArray<ATManBase*> TargetMans;
	UPROPERTY()
	ATMainTower* OwnTower;
	
	int32 ParallelAttackCount = 1;
	std::mutex AddMutex;
};
