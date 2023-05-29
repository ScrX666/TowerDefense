// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/ActorComp/TSoundManagerComponent.h"
#include "Component/ActorComp/TUIManagerComponent.h"
#include "GameFramework/PlayerController.h"
#include "TThirdPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATThirdPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UTSoundManagerComponent* SoundManagerComponent;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UTUIManagerComponent* UIManagerComponent;

public:
	ATThirdPlayerController();
};
