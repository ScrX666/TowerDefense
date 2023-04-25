// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/TMainBullet.h"

#include "Character/TManBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ATMainBullet::ATMainBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMoveComp"));
	SetRootComponent(Mesh);
	SphereComponent->SetupAttachment(RootComponent);

	// InitialLifeSpan = 2.0f;
}

void ATMainBullet::SphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	UE_LOG(LogTemp,Log,TEXT("Sphere Overlap"));
	if( Cast<ATManBase>(OtherActor))
	{
		UE_LOG(LogTemp,Log,TEXT("Sphere Overlap Cast Success"));
		if(OtherActor->Destroy())
		{
			UE_LOG(LogTemp,Log,TEXT("Destory Bullet OtherActor Success"));
		}
		else
		{
			UE_LOG(LogTemp,Log,TEXT("Destory Bullet OtherActor Fail"));
		}
		this->Destroy();
	}
}

// Called when the game starts or when spawned
void ATMainBullet::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ATMainBullet::SphereOverlap);
	
}

// Called every frame
void ATMainBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATMainBullet::Init(ATManBase* Target)
{
	ProjectileMovementComponent->HomingTargetComponent = Target->GetRootComponent();
}

