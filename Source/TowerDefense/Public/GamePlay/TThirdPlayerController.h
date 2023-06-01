// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TThirdPlayerController.generated.h"

class UTSoundManagerComponent;
class UTUIManagerComponent;
class UTDialogComponent;

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
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UTDialogComponent* DialogComponent;

public:
	ATThirdPlayerController();
};
