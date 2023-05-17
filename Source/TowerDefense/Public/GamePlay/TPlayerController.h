// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enum/EBuildingMode.h"
#include "GameFramework/PlayerController.h"
#include "Interface/TBuildingInterface.h"
#include "TPlayerController.generated.h"

class UTUIManagerComponent;
class ATPlayerState;
enum class EBuildingMode : uint8;
class ATMainBuilding;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	ATPlayerState* TPlayerState;
	UPROPERTY(VisibleAnywhere)
	UTUIManagerComponent* UIManagerComponent;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	ATMainBuilding* SelectedBuilding; // 选中的建筑

private:
	EBuildingMode BuildingMode = EBuildingMode::E_NotInBuildMode;
	TSubclassOf<AActor> BuildingClass;
	FVector CursorLocation;
	UPROPERTY()
	TScriptInterface<ITBuildingInterface> BuildingReferInterface; // 正在建造
	UPROPERTY()
	AActor* BuildingReferActor; // 正在建造
	UPROPERTY()
	TScriptInterface<ITBuildingInterface> CursorHitBuildingInterface; // 点击已经建造
	UPROPERTY()
	AActor* CursorHitBuildingActor; // 点击已经建造
	UPROPERTY()
	class UDecalComponent* DecalComponent;
	UPROPERTY()
	class ATMainAttachBase* AttachBase;
	UPROPERTY(EditAnywhere)
	class UMaterialInterface* DecalMaterial;
	
	
	bool CanConstruct;
	
public:
	ATPlayerController();
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	/*
	 * 设置建造模式（拿起，放下）
	 */
	UFUNCTION(BlueprintCallable)
	void SetBuildingMode(TSubclassOf<AActor> BuildingCla);

	UFUNCTION()
	void MouseClickDown();
	UFUNCTION()
	void MouseMove(float Value);

private:
	/*
	 * 放下
	 */
	void BuildingModeOff();
	/*
	 * 拿起
	 */
	void BuildingModeOn();
	
	UFUNCTION()
	void OnGameEnd(bool IsWin);
};
