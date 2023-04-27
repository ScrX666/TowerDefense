// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ActorComp/TManStateAndBuffer.h"



// Sets default values for this component's properties
UTManStateAndBuffer::UTManStateAndBuffer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTManStateAndBuffer::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTManStateAndBuffer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTManStateAndBuffer::ApplyHealthChange(AActor* Instigator,int Delta)
{
	CurrentHealth += Delta;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0, ManState.MaxHealth);
	OnHealthChanged.Broadcast(Instigator,this, CurrentHealth,Delta);
	//TODO: 添加死亡事件
	if( CurrentHealth == 0)
		OnDead.Broadcast();
}

