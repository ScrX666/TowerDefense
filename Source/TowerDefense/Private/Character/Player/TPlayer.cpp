// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/TPlayer.h"

#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ATPlayer::ATPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Root"));
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = SphereComponent;
	CameraComponent->SetupAttachment(SpringArmComponent,USpringArmComponent::SocketName);
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->TargetArmLength = 2500.0f;
	SpringArmComponent->SetRelativeRotation(FRotator(-40.0f, 0.0f, 0.0f));

	CameraMinZoom = 1000.0f;
	CameraMaxZoom = 5000.0f;
	CameraZoomSpeed = 100.0f;
	CameraMoveSpeed = 100.0f;
	
}

// Called when the game starts or when spawned
void ATPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



// Called to bind functionality to input
void ATPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("CameraZoom"),this,&ATPlayer::CameraZoom);

	// 暂时没有需求
	// PlayerInputComponent->BindAxis(TEXT("CameraMoveRight"),this,&ATPlayer::CameraMoveRight);
	// PlayerInputComponent->BindAxis(TEXT("CameraMoveFront"),this,&ATPlayer::CameraMoveFront);
}

/*
 * 摄像机放大缩小
 */
void ATPlayer::CameraZoom(float Value)
{
	SpringArmComponent->TargetArmLength += Value * CameraZoomSpeed;
	SpringArmComponent->TargetArmLength = FMath::Clamp(SpringArmComponent->TargetArmLength,CameraMinZoom,CameraMaxZoom);
}
/*
 * 摄像机移动
 */
void ATPlayer::CameraMoveRight(float Value)
{
	FVector Loc = this->GetActorLocation();
	FVector Dir = CameraComponent->GetRightVector();
	this->SetActorLocation(Loc + Dir * Value * CameraMoveSpeed);
}

void ATPlayer::CameraMoveFront(float Value)
{
	FVector Loc = this->GetActorLocation();
	FVector Dir = CameraComponent->GetForwardVector();
	this->SetActorLocation(Loc + Dir * Value * CameraMoveSpeed);
}