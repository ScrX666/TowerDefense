// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/TDialogEventInterface.h"
#include "TBaseDialogEvent.generated.h"

UCLASS()
class TOWERDEFENSE_API ATBaseDialogEvent : public AActor, public ITDialogEventInterface
{
	GENERATED_BODY()
public:
	virtual void TriggerDialogEvent_Implementation(UWorld* World) override;
};
