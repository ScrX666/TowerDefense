// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/TBaseItem.h"
#include "TBaseDialogItem.generated.h"

class UDataTable;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATBaseDialogItem : public ATBaseItem
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UDataTable* DialogTable;
public:
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
};
