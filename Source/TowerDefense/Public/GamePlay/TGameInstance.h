// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Building/Tower/TMainTower.h"
#include "Engine/GameInstance.h"
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
	UPROPERTY(BlueprintReadOnly)
	UTexture2D* LoadingTexture;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> LoadingUICla;
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<ATMainTower>> InitTowers; // 初始时拥有的塔
	UPROPERTY(BlueprintReadOnly)
	float MusicVolume = 1.0f;
	UPROPERTY(BlueprintReadOnly)
	float SoundVolume = 1.0f;
private:
	UPROPERTY(VisibleAnywhere)
	TArray<TSubclassOf<ATMainTower>> OwnTowers; // 拥有的塔
public:
	UFUNCTION(BlueprintCallable)
	bool AddTower(TSubclassOf<ATMainTower> Tower);
	UFUNCTION(BlueprintCallable)
	const TArray<TSubclassOf<ATMainTower>>& GetOwnTowers();

	virtual void Init() override;
 
	UFUNCTION()
	virtual void BeginLoadingScreen(const FString& MapName);
	UFUNCTION()
	virtual void EndLoadingScreen(UWorld* World);
};
