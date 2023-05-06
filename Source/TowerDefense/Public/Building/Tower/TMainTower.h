// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Building/TMainBuilding.h"
#include "Structure/FTTower.h"
#include "TMainTower.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATMainTower : public ATMainBuilding
{
	GENERATED_BODY()
public:
	ATMainTower();
	UPROPERTY()
	class ATManBase* TargetMan;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	class USceneComponent* AttackRangeComps;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	class UStaticMeshComponent* AttackRangeMesh;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	class USphereComponent* AttackRangeSphere;
	UPROPERTY(EditDefaultsOnly)
	FName Name;
	
	// UPROPERTY(VisibleAnywhere)
	// FTTower TowerData;
protected:
	

private:
	float AttackRange;


public:
	virtual void Fire();
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
	
	virtual void GetExp(int Exp);
	
protected:
	virtual void TargetInRange();
	virtual void NoTargetInRange();
private:
		
	
};
