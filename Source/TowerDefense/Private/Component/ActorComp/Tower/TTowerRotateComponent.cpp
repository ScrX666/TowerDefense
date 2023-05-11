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

	// ...
}


// Called when the game starts
void UTTowerRotateComponent::BeginPlay()
{
	Super::BeginPlay();

	if( !Tower)
	{
		UE_LOG(LogTemp,Warning,TEXT("The default rotate object is the tower"));
		Tower = Cast<ATMainTower>(GetOwner());
		if( !RotateActor) RotateActor = Tower;
	}
	
}


// Called every frame
void UTTowerRotateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if( Tower &&
		RotateActor &&
		Tower->AttackHandleComponent &&
		!Tower->AttackHandleComponent->TargetIsEmpty())
	{
		const FMatrix NewMatrix = FRotationMatrix::MakeFromX(Tower->AttackHandleComponent->ReturnTargetLocation() - RotateActor->GetActorLocation());
		const float NewYawValue = NewMatrix.Rotator().Yaw;
		FRotator TargetRotator = NewMatrix.Rotator();
		TargetRotator.Pitch = 0;
		TargetRotator.Roll = 0;
		RotateActor->SetActorRotation(FMath::RInterpConstantTo(RotateActor->GetActorRotation(),TargetRotator,DeltaTime,RotateSpeed));
		// CurRotator.Yaw = FMath::Clamp(DeltaTime* RotateSpeed,CurRotator.Yaw,NewYawValue);
		// Tower->SetActorRotation(CurRotator);
	}
}

