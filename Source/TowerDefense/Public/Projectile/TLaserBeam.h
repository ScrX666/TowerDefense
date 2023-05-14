// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structure/FTManBuffer.h"
#include "Character/TManBase.h"
#include "GameFramework/Actor.h"
#include "TLaserBeam.generated.h"

UCLASS()
class TOWERDEFENSE_API ATLaserBeam : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATLaserBeam();

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	class UNiagaraComponent* NiagaraComp;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UAudioComponent* AudioComp;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Scale;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector EndPos;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FColor Color;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USoundBase* Sound;

private:
	UPROPERTY()
	ATManBase* TargetMan;

	FTimerHandle DamageTimerHandle;

	float Damage;
	// 要施加的Buff
	const TArray<FTManBuffer>* BuffersPointer;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnConstruction(const FTransform& Transform) override;
	void Init(ATManBase* InTarget, float InitDamage,const TArray<FTManBuffer> &Buffers);
	void DoDamge();
	void SetBeamLocation();
	
	void SetDamage(float NewDamage);
	
	
	ATManBase* GetTargetMan() const;
};
