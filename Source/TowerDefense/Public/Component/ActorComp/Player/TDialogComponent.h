// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/TDialogEventInterface.h"
#include "TDialogComponent.generated.h"


class UDataTable;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UTDialogComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere)
	TMap<TSubclassOf<UObject>,TScriptInterface<ITDialogEventInterface>> DialogEvents;
	UPROPERTY(BlueprintReadOnly)
	UDataTable* CurDialogTable;
	
protected:
	virtual void BeginPlay() override;

public:	
	UTDialogComponent();

	UFUNCTION(BlueprintCallable)
	void ExecuteDialogEvent(TSubclassOf<UObject> DialogEventCla);
	UFUNCTION(BlueprintCallable)
	void TriggerDialog(UDataTable* DialogTable);
};
