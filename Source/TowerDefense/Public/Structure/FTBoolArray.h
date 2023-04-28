// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FTBoolArray.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType) 
struct FTBoolArray
{
	GENERATED_USTRUCT_BODY()
 
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<bool> Array;

	FTBoolArray();
	FTBoolArray(int Length);

	bool& operator[](int Index);
	
};
