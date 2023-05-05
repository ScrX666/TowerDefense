// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface/TStackStateInterface.h"
#include "TUIState.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTUIState : public UUserWidget,public ITStackStateInterface
{
	GENERATED_BODY()
public:
	virtual void EnterState(EStackAction StackAction) override;
	virtual void ExitState(EStackAction StackAction) override;
	virtual void UpdateState(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent,Category = "StackState")
	void ReceiveEnterState(EStackAction StackAction);
	UFUNCTION(BlueprintNativeEvent,Category = "StackState")
	void ReceiveExitState(EStackAction StackAction);
	UFUNCTION(BlueprintNativeEvent,Category = "StackState")
	void ReceiveUpdateState(float DeltaTime);
};
