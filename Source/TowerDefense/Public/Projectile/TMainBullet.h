// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TMainBullet.generated.h"

class ATManBase;

UCLASS()
class TOWERDEFENSE_API ATMainBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATMainBullet();

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* SphereComponent;
	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* ProjectileMovementComponent;
	
protected:
	UFUNCTION()
	void SphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Init(ATManBase* Target);
};
