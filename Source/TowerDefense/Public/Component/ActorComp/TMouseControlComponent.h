// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enum/EBuildingMode.h"
#include "Interface/TBuildingInterface.h"
#include "TMouseControlComponent.generated.h"

class UTSkillManagerComponent;
class UTUIManagerComponent;
class ATPlayerState;
class UBlackboardComponent;
class ATHeroController;
class ATPlayerController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnConstructTower, ATMainTower*, Tower, bool, bIsConstruct);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UTMouseControlComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere,BlueprintAssignable,BlueprintCallable)
	FOnConstructTower OnConstructTower;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	ATPlayerState* TPlayerState;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	TScriptInterface<ITBuildingInterface> SelectedBuilding; // 选中的建筑
	
private:
	
	FName CurSkillName; // 即将释放的技能名字
	
	UPROPERTY()
	ATPlayerController* PC;
	UPROPERTY()
	UTSkillManagerComponent* SkillManagerComponent;
	
	EBuildingMode BuildingMode = EBuildingMode::E_NotInBuildMode;
	TSubclassOf<AActor> BuildingClass;
	FVector CursorLocation;
	// ---------------------------------
	UPROPERTY()
	TScriptInterface<ITBuildingInterface> BuildingReferInterface; // 正在建造
	UPROPERTY()
	AActor* BuildingReferActor; // 正在建造
	// ---------------------------------
	UPROPERTY()
	TScriptInterface<ITBuildingInterface> CursorHitBuildingInterface; // 点击已经建造
	UPROPERTY()
	AActor* CursorHitBuildingActor; // 点击已经建造
	// ---------------------------------
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

	UPROPERTY()
	UTUIManagerComponent* UIManagerComponent;
	
public:	
	// Sets default values for this component's properties
	UTMouseControlComponent();

	virtual void InitializeComponent() override;

	
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
	FVector GetCursorHitLoc() const;
	/*
	 * 设置建造模式（拿起，放下）
	 */
	UFUNCTION(BlueprintCallable)
	void SetBuildingMode(TSubclassOf<AActor> BuildingCla);
	
	/*
	 * 绑定到委托
	 */
	UFUNCTION()
	void OnConstructTowerBulid(ATMainTower* Tower,bool bIsConstruct);
	/*
	 * 绑定到委托
	 */
	UFUNCTION()
	void OnSelectHero(bool bSelectHero);
	/*
	 * 绑定到输入事件
	 */
	UFUNCTION()
	void MouseMove(float Value);
	/*
	 * 绑定到输入事件 右键
	 */
	UFUNCTION()
	void MouseRightClickDown();
	/*
	 * 绑定到输入事件 左键
	 */
	UFUNCTION()
	void MouseClickDown();
	
protected:
	virtual void BeginPlay() override;

private:

	/*
	 * 放下
	 */
	void BuildingModeOff();
	/*
	 * 拿起
	 */
	void BuildingModeOn();
};
