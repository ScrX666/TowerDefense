// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/TBaseSkill.h"
#include "THeroSkill.generated.h"

class ATHero;
/**
 * 
 */
UCLASS(Blueprintable)
class TOWERDEFENSE_API UTHeroSkill : public UTBaseSkill
{
	GENERATED_BODY()
private:
	UPROPERTY()
	ATHero* Hero;
public:
	virtual void Execute(UWorld* World) override;
	void ExactlyExecute();
protected:
	virtual void OnCoolDownUpdate() override;
};
