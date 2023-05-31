// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/TDialogEventInterface.h"
#include "TDialogComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UTDialogComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere)
	TMap<TSubclassOf<UTDialogEventInterface>,TScriptInterface<UTDialogEventInterface>> DialogEvents;
public:	
	// Sets default values for this component's properties
	UTDialogComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ExecuteDialogEvent(TSubclassOf<UTDialogEventInterface> DialogEventCla);
};
