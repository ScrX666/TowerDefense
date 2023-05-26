// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Building/Tower/TMainTower.h"
#include "Components/ActorComponent.h"
#include "TSoundManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UTSoundManagerComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere)
	UAudioComponent* AmbientSoundComp;
	UPROPERTY(VisibleAnywhere)
	UAudioComponent* BackgroundSoundComp;
	
	UPROPERTY(EditDefaultsOnly)
	USoundBase* ClickHeroSound;
	UPROPERTY(EditDefaultsOnly)
	USoundBase* WinGameSound;
	UPROPERTY(EditDefaultsOnly)
	USoundBase* FailGameSound;
	UPROPERTY(EditDefaultsOnly)
	USoundBase* BuildSound;
	UPROPERTY(EditDefaultsOnly)
	USoundBase* DestorySound;
	UPROPERTY(EditDefaultsOnly)
	USoundBase* UIClickSound;
	
	UPROPERTY()
	USoundBase* AmbientSound;
	UPROPERTY()
	USoundBase* BackgroundSound;
public:	
	// Sets default values for this component's properties
	UTSoundManagerComponent();
	UFUNCTION()
	void SetBgAndAmSound(USoundBase* AmSound,USoundBase* BGSound);
	UFUNCTION()
	void PlayAmbientSound();
	UFUNCTION()
	void PlayBackgroundSound();

	void PlayHeroClickSound();
	UFUNCTION()
	void OnSelectHero(bool bIsSelected);
	UFUNCTION(BlueprintCallable)
	void OnBtnClick();
	/*
	 * 游戏结束播放音效，通过委托触发
	 */
	UFUNCTION()
	void OnGameEnd(bool bIsWin);
	/*
	 * 创建删除塔播放音效，通过委托触发
	 */
	UFUNCTION()
	void OnConstructTowerBulid(ATMainTower* Tower, bool bIsConstruct);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
};
