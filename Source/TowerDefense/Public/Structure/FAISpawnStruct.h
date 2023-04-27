// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	float SpawnWave;
	
};


