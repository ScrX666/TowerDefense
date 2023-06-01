// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Structure/FTBoolArray.h"
#include "Structure/FTDialogData.h"
#include "TBlueprintFunctionLibrary.generated.h"


class UDataTable;
class ATMainTower;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable)
	static TArray<FTBoolArray> GetRandomPath(int32 Width, int32 Length, int32 N);
	UFUNCTION(BlueprintCallable)
	static FName GetNextLevel(const FName CurrentLevelName);
	UFUNCTION(BlueprintCallable)
	static int32 GetTowerCoinsByClassAndName(TSubclassOf<ATMainTower> Tower,FName Name);
	UFUNCTION(BlueprintCallable)
	static bool GetDialogFromTable(UDataTable* DataTable,FName RowName,FTDialogData& FindResult);
	UFUNCTION(BlueprintCallable)
	static TArray<AActor*> GetAllActorofClass(UWorld* World,TSubclassOf<AActor> ActorCla);

public:
	UFUNCTION(BlueprintCallable)
	static void PlayRandomSound(UObject* WorldContext, const TArray<USoundBase*>& Sounds, FVector Location);
};
