// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TThirdCharacter.generated.h"
/*
 * 第三人称移动人物
 */
UCLASS()
class TOWERDEFENSE_API ATThirdCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	class USphereComponent* DetectComp;
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere)
	class UTInteractComponent* InteractComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed;


public:
	// Sets default values for this character's properties
	ATThirdCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void PostInitializeComponents() override;
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	/*
	 * 前移动，绑定到inputaxis
	 */
	void MoveForward(float X);
	/*
	 * 右移动，绑定到inputaxis
	 */
	void MoveRight(float X);
	/*
	 * 与场景物体互动
	 */
	void PrimaryInteract();

		
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
