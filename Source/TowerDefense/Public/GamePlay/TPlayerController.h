// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enum/EBuildingMode.h"
#include "GameFramework/PlayerController.h"
#include "Interface/TBuildingInterface.h"
#include "TPlayerController.generated.h"

class ATMainTower;
class UTSoundManagerComponent;
class UTCursorManagerComponent;
class UTSkillManagerComponent;
class ATHeroController;
class UBlackboardComponent;
class UTUIManagerComponent;
class ATPlayerState;
enum class EBuildingMode : uint8;
class ATMainBuilding;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnConstructTower,ATMainTower*,Tower,bool,bIsConstruct);
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere,BlueprintAssignable,BlueprintCallable)
	FOnConstructTower OnConstructTower;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	ATPlayerState* TPlayerState;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UTUIManagerComponent* UIManagerComponent;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UTSkillManagerComponent* SkillManagerComponent;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UTSoundManagerComponent* SoundManagerComponent;
	// UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	// UTCursorManagerComponent* CursorManagerComponent;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TScriptInterface<ITBuildingInterface> SelectedBuilding; // 选中的建筑
	UPROPERTY(EditDefaultsOnly)
	bool bIsTest; // 测试

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


	FHitResult HitResult;
	bool bCanConstruct;
	bool bInHeroControlMode; // 是否在操控英雄的模式
	UPROPERTY(VisibleAnywhere)
	UBlackboardComponent* HeroBlackboardComponent;
	UPROPERTY(VisibleAnywhere)
	ATHeroController* HeroAIC;

	FName CurSkillName; // 即将释放的技能名字
	
public:
	ATPlayerController();
	UFUNCTION()
	void OnConstructTowerBulid(ATMainTower* Tower,bool bIsConstruct);
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void OnEscBtnPress();
	virtual void SetupInputComponent() override;
	/*
	 * 设置建造模式（拿起，放下）
	 */
	UFUNCTION(BlueprintCallable)
	void SetBuildingMode(TSubclassOf<AActor> BuildingCla);
	/*
	 *  准备执行技能
	 */
	UFUNCTION(BlueprintCallable)
	void ExecuteSkill(FName SkillName);
	/*
	 * 实际执行技能
	 */
	void ConfirmExecuteSkill();

	UFUNCTION()
	void MouseClickDown();
	UFUNCTION()
	void MouseMove(float Value);
	UFUNCTION()
	FVector GetCursorHitLoc() const;
	
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
	void OnGameEnd(bool bIsWin);
	UFUNCTION()
	void OnSelectHero(bool bSelectHero);
};
