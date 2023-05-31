// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ActorComp/Player/TInteractComponent.h"

#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"
#include "Interface/TInteractInterface.h"

// Sets default values for this component's properties
UTInteractComponent::UTInteractComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


}


// Called when the game starts
void UTInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UTInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTInteractComponent::PrimaryInteract()
{
#pragma region 射线检测方式
	// FCollisionObjectQueryParams ObjectQueryParams;
	// ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	//
	// AActor* MyOwner = GetOwner();
	// FVector EyeLocation;
	// FRotator EyeRotation;
	// MyOwner->GetActorEyesViewPoint(EyeLocation,EyeRotation);
	//
	// FVector End = EyeRotation.Vector() * 1000.0f + EyeLocation;
	//
	// // FHitResult Hit;
	// // GetWorld()->LineTraceSingleByObjectType(Hit,EyeLocation,End, ObjectQueryParams);
	// // AActor* HitActor = Hit.GetActor();
	// float SphereRadius = 30.0f;
	// TArray<FHitResult> Hits;
	// FCollisionShape Shape;
	// Shape.SetSphere(SphereRadius);
	// bool bBlockHit = GetWorld()->SweepMultiByObjectType(Hits,EyeLocation, End, FQuat::Identity,ObjectQueryParams,Shape);
	// FColor Color = bBlockHit ? FColor::Red : FColor::Green;
	// for( FHitResult HitResult : Hits)
	// {
	// 	AActor* HitActor = HitResult.GetActor();
	// 	if( HitActor)                                                   
	// 	{                                                               
	// 		if( HitActor->Implements<UTInteractInterface>())            
	// 		{                                                           
	// 			APawn* MyPawn = Cast<APawn>(MyOwner);                   
	// 			ITInteractInterface::Execute_Interact(HitActor, MyPawn);
	// 			break;
	// 		}                                                           
	// 	}
	// 	DrawDebugSphere(GetWorld(),HitResult.ImpactPoint,SphereRadius,32,Color,false,2.0f);
	// }
	// DrawDebugLine(GetWorld(),EyeLocation,End,Color,false, 2.0f);
#pragma endregion

	if( DetectedActors.Num() != 0)
	{
		ITInteractInterface::Execute_Interact(DetectedActors[0]->_getUObject(), nullptr);
	}
}

void UTInteractComponent::OnEnterDetectRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if( OtherActor->Implements<UTInteractInterface>())
	{
		DetectedActors.AddUnique(OtherActor);
		ITInteractInterface::Execute_ActiveTipsUI(OtherActor,true);
	}
}

void UTInteractComponent::OnExitDetectRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if( OtherActor->Implements<UTInteractInterface>())
	{
		DetectedActors.Remove(OtherActor);
		ITInteractInterface::Execute_ActiveTipsUI(OtherActor,false);
	}
}
