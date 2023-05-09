// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enum/EManBufferType.h"
#include "Engine/DataTable.h"
#include "FTManBuffer.generated.h"

class UNiagaraSystem;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FTManBuffer : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly)
	EManBufferType BufferType;
	UPROPERTY(EditDefaultsOnly)
	float DurationTime;
	/*
	 * Ice: 减速的比例
	 * Poison: 掉血的伤害
	 */
	UPROPERTY(EditDefaultsOnly)
	float EffectNum;
	UPROPERTY(EditDefaultsOnly)
	UNiagaraSystem* NiagaraEffect;
};

