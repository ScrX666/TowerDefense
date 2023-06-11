// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Building/TMainBuilding.h"
#include "Structure/FTManBuffer.h"
#include "TMainTower.generated.h"

class UTTowerStateComponent;
struct FTTowerAbility;
class UTAttackHandleComponent;
class ATManBase;
class USphereComponent;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATMainTower : public ATMainBuilding
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USceneComponent* AttackRangeComps;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UStaticMeshComponent* AttackRangeMesh;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USphereComponent* AttackRangeSphere;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UTAttackHandleComponent* AttackHandleComponent;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	FName Name;
	
	// UPROPERTY(VisibleAnywhere)
	// FTTower TowerData;
protected:
	// int32 ParallelAttackCount = 1;
	UPROPERTY()
	TArray<FTManBuffer> ApplyBuffers;
	
private:
	float AttackRange;

public:
	ATMainTower();
	virtual void Fire();
	
	UFUNCTION(BlueprintCallable)
	virtual void OnSelected(bool bSelected) override;
	
	// 接口
	virtual void OnConstruct(ATMainAttachBase* AttachBase) override;
	virtual void BeginPlay() override;

	// unreal 自带
	virtual void OnConstruction(const FTransform& Transform) override;
	
	UFUNCTION()
	void AttackRangeOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void AttackRangeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void UpdateAttackRange(const float NewRange);

	/*
	 * 获取Exp
	 */
	virtual void GetExp(int Exp);
	/*
	 * 添加Buff
	 */
	virtual void AddBuffer(const FTManBuffer& Buffer);

	UFUNCTION(BlueprintPure)
	virtual UTTowerStateComponent* GetStateComp() const ;
	
protected:
	virtual void TargetInRange();
	virtual void NoTargetInRange();
private:
		
	
};
