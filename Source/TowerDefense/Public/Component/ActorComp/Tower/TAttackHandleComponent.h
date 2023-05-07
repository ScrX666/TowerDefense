// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TAttackHandleComponent.generated.h"


class ATManBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UTAttackHandleComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTAttackHandleComponent();

	/*
	 * 能够攻击的敌人数量是否已经满了
	 */
	bool TargetIsFull();
	/*
	 * 能够攻击的敌人数量是否已经满了
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
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:
	UPROPERTY()
	TArray<ATManBase*> TargetMans;
		
	int32 ParallelAttackCount = 1;
};
