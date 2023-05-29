// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/TThirdCharacter.h"

#include "Camera/CameraComponent.h"
#include "Component/ActorComp/Player/TInteractComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

ATThirdCharacter::ATThirdCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DetectComp = CreateDefaultSubobject<USphereComponent>(TEXT("DetectComp"));
	DetectComp->SetCollisionProfileName(TEXT("DetectInteract"));
	DetectComp->SetSphereRadius(200.0f);
	DetectComp->SetupAttachment(RootComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	InteractComponent = CreateDefaultSubobject<UTInteractComponent>(TEXT("InteractComp"));
	CameraComponent->SetupAttachment(SpringArmComponent,USpringArmComponent::SocketName);
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->TargetArmLength = 250.0f;
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SocketOffset.Y = 90.0f;
	
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	MoveSpeed = 100.0f;

}

// Called when the game starts or when spawned
void ATThirdCharacter::BeginPlay()
{
	Super::BeginPlay();
	DetectComp->OnComponentBeginOverlap.AddDynamic(InteractComponent, &UTInteractComponent::OnEnterDetectRange);
	DetectComp->OnComponentEndOverlap.AddDynamic(InteractComponent, &UTInteractComponent::OnExitDetectRange);
}

// Called every frame
void ATThirdCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ATThirdCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ATThirdCharacter::MoveForward(float Value)
{
	FRotator ContollRotat = GetControlRotation();
	// 防止往地下走
	ContollRotat.Pitch = 0.0f;
	ContollRotat.Roll = 0.0f;
	this->AddMovementInput(ContollRotat.Vector(),Value * MoveSpeed);
}

void ATThirdCharacter::MoveRight(float Value)
{
	FRotator ContollRotat = GetControlRotation();
	ContollRotat.Pitch = 0.0f;
	ContollRotat.Roll = 0.0f;
	this->AddMovementInput(UKismetMathLibrary::GetRightVector(ContollRotat),Value * MoveSpeed);
}


void ATThirdCharacter::PrimaryInteract()
{
	if( InteractComponent)
	{
		InteractComponent->PrimaryInteract();
	}
}

// Called to bind functionality to input
void ATThirdCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this,&ATThirdCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this,&ATThirdCharacter::MoveRight);	
	PlayerInputComponent->BindAxis("TurnYaw", this,&APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnPitch", this,&APawn::AddControllerPitchInput);
	
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed,this,&ATThirdCharacter::PrimaryInteract);
}