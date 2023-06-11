// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enum/EShowMessageType.h"
#include "GameFramework/PlayerController.h"
#include "TPlayerController.generated.h"

class UTMouseControlComponent;
class UTDialogComponent;
class UTSoundManagerComponent;
class UTCursorManagerComponent;
class UTSkillManagerComponent;
class ATHeroController;
class UBlackboardComponent;
class UTUIManagerComponent;
class ATPlayerState;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShowMessage,TEnumAsByte<EShowMessageType>, MessageType);

/**
 * 塔防游戏PlayerController
 */
UCLASS()
class TOWERDEFENSE_API ATPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	ATPlayerState* TPlayerState;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UTUIManagerComponent* UIManagerComponent;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UTSkillManagerComponent* SkillManagerComponent;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UTSoundManagerComponent* SoundManagerComponent;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UTDialogComponent* DialogComponent;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UTMouseControlComponent* MouseControlComponent;
	// UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	// UTCursorManagerComponent* CursorManagerComponent;
	UPROPERTY(EditDefaultsOnly)
	bool bIsTest; // 测试
	UPROPERTY(VisibleAnywhere,BlueprintAssignable)
	FOnShowMessage OnShowMessage;

private:

	UPROPERTY(VisibleAnywhere)
	UBlackboardComponent* HeroBlackboardComponent;
	UPROPERTY(VisibleAnywhere)
	ATHeroController* HeroAIC;
	
public:
	ATPlayerController();
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
	UFUNCTION(BlueprintCallable)
	void OnEscBtnPress();
private:

	/*
	 * 绑定到Gamemode的委托
	 */
	UFUNCTION()
	void OnGameEnd(bool bIsWin);
	/*
	 * 绑定到Gamemode的委托
	 */
	UFUNCTION()
	void OnGameReallyStart();
};
