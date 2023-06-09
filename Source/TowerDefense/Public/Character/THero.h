// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TSoldierBase.h"
#include "THero.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectHero,bool,bIsSelected);
class UNiagaraComponent;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATHero : public ATSoldierBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	TArray<USoundBase*> RebornSounds;
	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* SelectedEffect;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UStaticMeshComponent* WeaponMeshComp;
	UPROPERTY(VisibleAnywhere,BlueprintAssignable)
	FOnSelectHero OnSelectHero;
public:
	ATHero();
	virtual void OnSelected(bool bIsSelected) override;
	virtual void OnManDead() override;
	virtual void OnManReborn() override;
	virtual void BeginPlay() override;
};
