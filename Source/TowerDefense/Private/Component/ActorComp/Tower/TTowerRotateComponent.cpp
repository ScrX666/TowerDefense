// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ActorComp/Tower/TTowerRotateComponent.h"

#include "Building/Tower/TMainTower.h"
#include "Component/ActorComp/Tower/TAttackHandleComponent.h"

// Sets default values for this component's properties
UTTowerRotateComponent::UTTowerRotateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	RotateSpeed = 120.0f;
	// bUseRootAsRotate = true;
	// ...
}


// Called when the game starts
void UTTowerRotateComponent::BeginPlay()
{
	Super::BeginPlay();

	Tower = Cast<ATMainTower>(GetOwner());
	if( !RotateComponent)
	{
		UE_LOG(LogTemp,Log,TEXT("The default rotate Comp is the tower RootComp"));
		RotateComponent = GetOwner()->GetRootComponent();
	}
	
}


// Called every frame
void UTTowerRotateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if( RotateComponent &&
		Tower->AttackHandleComponent &&
		!Tower->AttackHandleComponent->TargetIsEmpty())
	{
		const FMatrix NewMatrix = FRotationMatrix::MakeFromX(Tower->AttackHandleComponent->ReturnTargetLocation() - RotateComponent->GetComponentLocation());
		FRotator TargetRotator = NewMatrix.Rotator();
		TargetRotator.Pitch = 0;
		TargetRotator.Roll = 0;
		RotateComponent->SetWorldRotation(FMath::RInterpConstantTo(RotateComponent->GetComponentRotation(),TargetRotator,DeltaTime,RotateSpeed));
		// CurRotator.Yaw = FMath::Clamp(DeltaTime* RotateSpeed,CurRotator.Yaw,NewYawValue);
		// Tower->SetActorRotation(CurRotator);
	}
}

