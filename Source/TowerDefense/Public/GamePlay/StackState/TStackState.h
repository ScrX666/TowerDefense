// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/TStackStateInterface.h"
#include "UObject/NoExportTypes.h"
#include "TStackState.generated.h"

/**
 * 
 */
UCLASS(Abstract,BlueprintType,Blueprintable)
class TOWERDEFENSE_API UTStackState : public UObject,public ITStackStateInterface
{
	GENERATED_BODY()
public:
	virtual void EnterState(EStackAction StackAction) override;
	virtual void ExitState(EStackAction StackAction) override;
	virtual void UpdateState(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent,Category="StackState")
	void ReceiveEnterState(EStackAction StackAction);
	UFUNCTION(BlueprintImplementableEvent,Category="StackState")
	void ReceiveExitState(EStackAction StackAction);
	UFUNCTION(BlueprintImplementableEvent,Category="StackState")
	void ReceiveUpdateState(float DeltaTime);
};
