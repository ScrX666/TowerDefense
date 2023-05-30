// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/ActorComp/TStackStateMachineComponent.h"
#include "TUIManagerComponent.generated.h"

class UDataTable;

UENUM(BlueprintType)
enum EUIStateCastResult { Success,Failure };

class UTUIState;
/**
 * UI管理器
 */
UCLASS()
class TOWERDEFENSE_API UTUIManagerComponent : public UTStackStateMachineComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UDataTable* DialogTable; // 用作打开UI面板  和  对话面板读取数据的交换

	
	UPROPERTY(EditDefaultsOnly)
	TMap<FName,TSubclassOf<UTUIState>> UIStates;
	UPROPERTY(VisibleAnywhere)
	APlayerController* PlayerController;
private:
	UPROPERTY()
	TMap<FName,UTUIState*> UIInstances;
	
public:
	UFUNCTION(BlueprintNativeEvent)
	void InitUIState();
	UFUNCTION(BlueprintNativeEvent,BlueprintPure)
	UTUIState* GetUI(FName Name);
	UFUNCTION(BlueprintCallable)
	void PushUIState(FName UIName);
	UFUNCTION(BlueprintCallable)
	void GetCurrentUIState(TSubclassOf<UTUIState> StateClass,TEnumAsByte<EUIStateCastResult>& IsVaild,UTUIState*& OutState);

	UFUNCTION(BlueprintCallable)
	void OnESCPress();

	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
