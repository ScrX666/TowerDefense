// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Structure/FTManBuffer.h"
#include "TMainBullet.generated.h"

class ATManBase;

UCLASS()
class TOWERDEFENSE_API ATMainBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* SphereComponent;
	UPROPERTY(EditDefaultsOnly)
	TArray<USoundBase*> ExplosionSounds;

private:
	UPROPERTY(VisibleAnywhere)
	ATManBase* TargetMan;

	float Speed = 100.0f;
	int32 Damage = 50.0f;
	const TArray<FTManBuffer>* BuffersPointer;
public:
	ATMainBullet();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Init(ATManBase* InitTarget, float InitSpeed, int32 InitDamage,const TArray<FTManBuffer> &Buffers);
	
protected:
	UFUNCTION()
	void SphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
private:
	/*
	 * 手动模拟移动
	 */
	void BulletMove(float DeltaTime);
};
