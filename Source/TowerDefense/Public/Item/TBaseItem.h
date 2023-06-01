// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "Interface/TInteractInterface.h"
#include "TBaseItem.generated.h"

UCLASS()
class TOWERDEFENSE_API ATBaseItem : public AActor, public ITInteractInterface
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UStaticMeshComponent* MeshComponent;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UWidgetComponent* WidgetComponent;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	bool bIsItemActive;
	
protected:
	virtual void BeginPlay() override;

public:	
	ATBaseItem();

	UFUNCTION(BlueprintCallable)
	virtual void EnableItem(bool bActive);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "EnableItem"))
	void BlueprintEnableItem(bool bActive); // 留给蓝图完成相关操作
	
	void Interact(APawn* InstigatorPawn);

	virtual void ActiveTipsUI_Implementation(bool bIsActive) override;;
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
};
