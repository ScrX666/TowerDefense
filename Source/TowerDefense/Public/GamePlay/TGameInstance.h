// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Building/Tower/TMainTower.h"
#include "Engine/GameInstance.h"
#include "Structure/FTLoadingPanelInfo.h"
#include "TGameInstance.generated.h"

class UWidget;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	int LoadNum = 0;

	UPROPERTY(BlueprintReadWrite)
	bool bCompleteGame = false;
	
	UPROPERTY(BlueprintReadOnly)
	float TowerAttackRangeAmend = 1.0f; // 塔攻击范围的修正值

	// 关卡加载信息
	UPROPERTY(BlueprintReadOnly)
	FTLoadingPanelInfo LoadingPanelInfo;

	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> LoadingUICla;
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<ATMainTower>> InitTowers; // 初始时拥有的塔

	// 音量
	UPROPERTY(BlueprintReadOnly)
	float MusicVolume = 1.0f;
	UPROPERTY(BlueprintReadOnly)
	float SoundVolume = 1.0f;
private:
	UPROPERTY(VisibleAnywhere)
	TArray<TSubclassOf<ATMainTower>> OwnTowers; // 拥有的塔
public:
	/*
	 * 添加能够建造的塔
	 */
	UFUNCTION(BlueprintCallable)
	bool AddTower(TSubclassOf<ATMainTower> Tower);
	/*
	 * 获取所有能够建造的塔
	 */
	UFUNCTION(BlueprintCallable)
	const TArray<TSubclassOf<ATMainTower>>& GetOwnTowers();

	/*
	 * 每一关初始化
	 */
	virtual void Init() override;
 
	UFUNCTION()
	virtual void BeginLoadingScreen(const FString& MapName);
	UFUNCTION()
	virtual void EndLoadingScreen(UWorld* World);
};
