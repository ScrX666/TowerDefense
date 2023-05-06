// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/TStackStateInterface.h"
#include "TStackStateMachineComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStateEnterSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStateExitSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStateChangeSignature,TScriptInterface<ITStackStateInterface>,State);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UTStackStateMachineComponent : public UActorComponent,public ITStackStateInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTStackStateMachineComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	void PushState(TScriptInterface<ITStackStateInterface> NewState);
	UFUNCTION(BlueprintCallable)
	void PopState();
	UFUNCTION(BlueprintCallable)
	void PopStates(int Count);
	UFUNCTION(BlueprintCallable)
	void PopAllStates();

	// 接口实现
	virtual void EnterState(EStackAction StackAction) override;
	virtual void ExitState(EStackAction StackAction) override;
	virtual void UpdateState(float DeltaTime) override;

	// 蓝图回调
	UFUNCTION(BlueprintImplementableEvent,Category="StackStateMachine")
	void ReceiveEnterState(EStackAction StackAction);
	UFUNCTION(BlueprintImplementableEvent,Category="StackStateMachine")
	void ReceiveExitState(EStackAction StackAction);
	UFUNCTION(BlueprintImplementableEvent,Category="StackStateMachine")
	void ReceiveUpdateState(float DeltaTime);
	UFUNCTION(BlueprintImplementableEvent,Category="StackStateMachine")
	void ReceiveStatePushed(const TScriptInterface<ITStackStateInterface>& PushedState);
	UFUNCTION(BlueprintImplementableEvent,Category="StackStateMachine")
	void ReceiveStatePopped(const TScriptInterface<ITStackStateInterface>& PoppedState);

	// Getter
	UFUNCTION(BlueprintPure,Category = "StackStateMachine")
	TScriptInterface<ITStackStateInterface> GetCurrentState();
	UFUNCTION(BlueprintPure,Category = "StackStateMachine")
	TScriptInterface<ITStackStateInterface> GetUnderState();
	UFUNCTION(BlueprintPure,Category = "StackStateMachine")
	TScriptInterface<ITStackStateInterface> GetState(int32 Index);
	UFUNCTION(BlueprintPure,Category = "StackStateMachine")
	int32 StateCount() const;
	UFUNCTION(BlueprintPure,Category = "StackStateMachine")
	FORCEINLINE float GetCurrentStateTime() const;


	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// 由子类调用
	virtual void StatePushed(TScriptInterface<ITStackStateInterface> PushedState);
	virtual void StatePopped(TScriptInterface<ITStackStateInterface> PoppedState);
	
public:
	// Event Dispatcher
	UPROPERTY(BlueprintAssignable,Category="StackStateMachine")
	FOnStateEnterSignature OnStateEnter;
	UPROPERTY(BlueprintAssignable,Category="StackStateMachine")
	FOnStateExitSignature OnStateExit;
	UPROPERTY(BlueprintAssignable,Category="StackStateMachine")
	FOnStateChangeSignature OnStatePushed;
	UPROPERTY(BlueprintAssignable,Category="StackStateMachine")
	FOnStateChangeSignature OnStatePopped;
protected:

	TArray<TScriptInterface<ITStackStateInterface>> States;

	// 当前状态持续时间
	UPROPERTY(VisibleAnywhere)
	float CurrentStateTime = 0;
};
