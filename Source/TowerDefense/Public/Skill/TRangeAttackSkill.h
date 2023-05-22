// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/TBaseLocationSkill.h"
#include "TRangeAttackSkill.generated.h"

class UNiagaraSystem;
/**
 * 
 */
UCLASS(Blueprintable)
class TOWERDEFENSE_API UTRangeAttackSkill : public UTBaseLocationSkill
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	float SkillRange = 100.0f;
	UPROPERTY(EditDefaultsOnly)
	float Damage = 50.0f;
	UPROPERTY(EditDefaultsOnly)
	UNiagaraSystem* NiagaraSystem;
public:
	virtual void Execute(UWorld* World) override;
};
