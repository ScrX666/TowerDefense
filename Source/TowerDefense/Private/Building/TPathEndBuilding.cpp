// Fill out your copyright notice in the Description page of Project Settings.


#include "Building/TPathEndBuilding.h"

#include "Character/TManBase.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TowerDefense/TowerDefenseGameModeBase.h"

ATPathEndBuilding::ATPathEndBuilding()
	:MaxHealth(100.0f),Health(100.0f)
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereComponent->SetupAttachment(RootComponent);
}

void ATPathEndBuilding::RangeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void ATPathEndBuilding::RangeOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if( OtherActor != nullptr && OtherActor->IsA<ATManBase>())
	{
		Health -= 10.0f;
		OnHomeHealthChanged.Broadcast(Health,-10.0f);
		
		if( Health <= 0.0f)
		{
			UE_LOG(LogTemp,Log,TEXT("Gaem End"));
			Cast<ATowerDefenseGameModeBase>(UGameplayStatics::GetGameMode(this))->OnGameEnd.Broadcast(false);	
		}
		OtherActor->Destroy();
	}
}

void ATPathEndBuilding::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ATPathEndBuilding::RangeOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ATPathEndBuilding::RangeEndOverlap);

}

bool ATPathEndBuilding::IsDead()
{
	return Health < 0.0f;
}


