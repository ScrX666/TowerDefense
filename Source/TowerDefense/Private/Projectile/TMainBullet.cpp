// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/TMainBullet.h"

#include "Character/TManBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATMainBullet::ATMainBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(Mesh);
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetGenerateOverlapEvents(true);

	
	// ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMoveComp"));
	// ProjectileMovementComponent->MaxSpeed = 1000.0f;
	// ProjectileMovementComponent->InitialSpeed = 0.0f;
	// ProjectileMovementComponent->bIsHomingProjectile = true;
	// ProjectileMovementComponent->HomingAccelerationMagnitude = 1000.0f;
	// ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	// ProjectileMovementComponent->Velocity = FVector::ZeroVector;
	//ProjectileMovementComponent->bRotationFollowsVelocity = true;
	
	
	// InitialLifeSpan = 2.0f;

	
}

void ATMainBullet::SphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	// UE_LOG(LogTemp,Log,TEXT("Sphere Overlap"));
	if( OtherActor->IsA<ATManBase>() && OtherActor == TargetMan)
	{
		UE_LOG(LogTemp,Log,TEXT("Sphere Overlap Cast Success"));
		// if(OtherActor->Destroy())
		// {
		// 	UE_LOG(LogTemp,Log,TEXT("Destory Bullet OtherActor Success"));
		// }
		// else
		// {
		// 	UE_LOG(LogTemp,Log,TEXT("Destory Bullet OtherActor Fail"));
		// }
		UGameplayStatics::ApplyDamage(OtherActor,50.0f, UGameplayStatics::GetPlayerController(this,0),this,UDamageType::StaticClass());
		this->Destroy();
	}
}

// Called when the game starts or when spawned
void ATMainBullet::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ATMainBullet::SphereOverlap);
	
}

void ATMainBullet::Destroyed()
{
	Super::Destroyed();
	SphereComponent->OnComponentBeginOverlap.Clear();
}

/*
 * 手动模拟移动
 */
void ATMainBullet::BulletMove(float DeltaTime)
{
	if( TargetMan)
	{
		FVector Direction = TargetMan->GetActorLocation() - this->GetActorLocation();
		Direction.Normalize();
		this->SetActorLocation(Direction * Speed * DeltaTime + this->GetActorLocation());
	}
}

// Called every frame
void ATMainBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	BulletMove(DeltaTime);
}

void ATMainBullet::Init(ATManBase* InitTarget, float InitSpeed, int32 InitDamage)
{
	TargetMan = InitTarget;
	Speed = InitSpeed;
	Damage = InitDamage;
}