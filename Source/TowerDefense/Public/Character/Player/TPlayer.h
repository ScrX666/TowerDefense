// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TPlayer.generated.h"

UCLASS()
class TOWERDEFENSE_API ATPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATPlayer();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	/*
	 * 摄像机放大缩小
	 */
	UFUNCTION()
	void CameraZoom(float Value);
	/*
	 * 摄像机移动
	 */
	UFUNCTION()
	void CameraMoveRight(float Value);
	UFUNCTION()
	void CameraMoveFront(float Value);
	
public:
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* SphereComponent;
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArmComponent;
private:
	// 摄像机移动相关参数
	UPROPERTY(EditDefaultsOnly)
	float CameraMinZoom;
	UPROPERTY(EditDefaultsOnly)
	float CameraMaxZoom;
	UPROPERTY(EditDefaultsOnly)
	float CameraZoomSpeed;
	UPROPERTY(EditDefaultsOnly)
	float CameraMoveSpeed;
	
};
