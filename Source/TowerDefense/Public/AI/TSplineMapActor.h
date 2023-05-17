// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "Structure/FAISpawnStruct.h"
#include "TSplineMapActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWaveChanged,int32,NewWave, int32, MaxWave);
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
	
protected:
	int32 CurrentWave = 0; // 当前波次
	int32 CurrentEnemyCount = 0; // 当前波次已经生成的敌人数量
	FTimerHandle WaveTimerHandle;
	FTimerHandle BeginplayTimerHandle;
	
protected:
	UPROPERTY(VisibleAnywhere)
	USplineComponent* SplineComponent;
	FVector FirstMoveLoc;

	FAISpawnStruct FaiSpawnStruct;
private:
	int CurrentExistEnemyCount = 0; // 场景中已经生成的敌人
	bool bFinishSpawn = false; // 是否已经生成完了

	TArray<FAISpawnStruct*> AISpawnData; //所有的敌人生成数据
	
	int32 WaveEnemyCount = 3; // 每波敌人数量
	int32 TotalWaveCount = 2; // 总波次数量
	float SpawnAIWalkSpeed = 500.0f; // 总波次数量
public:	
	// Sets default values for this actor's properties
	ATSplineMapActor();
	UFUNCTION()
	void MoveTo(ATFirstAIController* AIController, int index, FVector& NextPosition);

	void OnManDead();

	UFUNCTION(BlueprintCallable)
	int32 GetMaxWaveCount();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void AddArrow();
	UFUNCTION()
	void AIMove(ATFirstAIController* NPC);
	UFUNCTION()
	void SpawnAI();
	void SpawnWave();

};
