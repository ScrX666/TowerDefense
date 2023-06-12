// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "Structure/FAISpawnStruct.h"
#include "TSplineMapActor.generated.h"

class ATGameState;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWaveChanged, int32, NewWave, int32, MaxWave);
/**
 * @brief 敌人生成器
 */
UCLASS()
class TOWERDEFENSE_API ATSplineMapActor : public AActor
{
	GENERATED_BODY()
		
public:
	UPROPERTY(EditDefaultsOnly)
	bool bUseLevelNameAsTableSuffix = true; // 是否通过关卡名查表
	UPROPERTY(EditDefaultsOnly)
	FName TableNameSuffix;
	UPROPERTY(BlueprintAssignable)
	FOnWaveChanged OnWaveChanged;
	
	bool bFinishSpawn = false; // 是否已经生成完了
	
protected:
	int32 CurrentEnemyCount = 0; // 当前波 已经生成的敌人数量
	int32 CurrentWave = 0; // 当前波次
	FTimerHandle WaveTimerHandle;
	
	UPROPERTY(VisibleAnywhere)
	USplineComponent* SplineComponent;
	
	FVector FirstMoveLoc;

	FAISpawnStruct FaiSpawnStruct;
private:
	UPROPERTY()
	ATGameState* TGameState;
	int CurrentExistEnemyCount = 0; // 场景中已经生成的敌人

	TArray<FAISpawnStruct*> AISpawnData; //所有的敌人生成数据
	
	int32 WaveEnemyCount = 3; // 每波敌人数量
	int32 TotalWaveCount = 2; // 总波次数量
	float SpawnAIWalkSpeed = 500.0f; // 总波次数量
public:	
	ATSplineMapActor();
	UFUNCTION()
	void MoveTo(ATAIBaseController* AIController, int index, FVector& NextPosition);

	void OnManDead();

	UFUNCTION(BlueprintCallable)
	int32 GetMaxWaveCount();
	UFUNCTION(BlueprintCallable)
	FVector GetTargetPos(int32 index);
	UFUNCTION()
	void SpawnWave();

	FVector GetClosestPoint(FVector CurPos, int& CurIndex);
	
protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	void AIMove(ATAIBaseController* NPC);
	
	/*
	 * 生成AI 并初始化
	 */
	UFUNCTION()
	void SpawnAI();

};
