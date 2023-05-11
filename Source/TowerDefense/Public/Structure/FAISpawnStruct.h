// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TManBase.h"
#include "Engine/DataTable.h"
#include "FAISpawnStruct.generated.h"


/**
 * 
 */
USTRUCT(BlueprintType)
struct FAISpawnStruct : public FTableRowBase
{
	
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere,Category="AI")
	TSubclassOf<AActor> AICharacter;
	UPROPERTY(EditAnywhere,Category="AI")
	int32 SpawnAINums;
	UPROPERTY(EditAnywhere,Category="AI")
	float ManWalkSpeed = 250.0f;
	UPROPERTY(EditAnywhere,Category="AI")
	float TimeBetweenWave = 3.0f;
	UPROPERTY(EditAnywhere,Category="AI")
	float TimeBetweenSingle = 1.0f;
	
};


