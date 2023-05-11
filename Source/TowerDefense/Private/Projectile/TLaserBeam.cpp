// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/TLaserBeam.h"

#include "NiagaraComponent.h"
#include "Character/TManBase.h"
#include "Component/ActorComp/TManStateAndBuffer.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Structure/FTManBuffer.h"

// Sets default values
ATLaserBeam::ATLaserBeam()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("UNiagaraComp"));
	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	NiagaraComp->SetupAttachment(RootComponent);
	AudioComp->SetupAttachment(RootComponent);
	Damage = 0.0f;
}

// Called when the game starts or when spawned
void ATLaserBeam::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATLaserBeam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetBeamLocation();
	
}

void ATLaserBeam::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	NiagaraComp->SetVectorParameter(TEXT("User.BeamEnd"),EndPos);
	NiagaraComp->SetColorParameter(TEXT("User.Color"),Color);
	NiagaraComp->SetFloatParameter(TEXT("User.Scale"),Scale);
	AudioComp->SetSound(Sound);
}

void ATLaserBeam::Init(ATManBase* Target, float InitDamage,const TArray<FTManBuffer> &Buffers)
{
	UE_LOG(LogTemp,Log,TEXT("LaserBeam Change Target"));
	TargetMan = Target;
	if( TargetMan == nullptr)
	{
		SetActorHiddenInGame(true);
		return;
	}
	else
	{
		SetBeamLocation();
		SetActorHiddenInGame(false);
	}
	BuffersPointer = &Buffers;
	GetWorld()->GetTimerManager().ClearTimer(DamageTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(DamageTimerHandle,this,&ATLaserBeam::DoDamge,0.1f,true,0.0f);
	SetDamage(InitDamage);
}


void ATLaserBeam::DoDamge()
{
	// Damage
	UGameplayStatics::ApplyDamage(TargetMan,Damage, UGameplayStatics::GetPlayerController(this,0),this,UDamageType::StaticClass());

	// Buffer
	if(TargetMan && TargetMan->GetComponentByClass(UTManStateAndBuffer::StaticClass()))
		Cast<UTManStateAndBuffer>(TargetMan->GetComponentByClass(UTManStateAndBuffer::StaticClass()))
		->ActivateBuffer(*BuffersPointer,this->GetOwner());
}

void ATLaserBeam::SetBeamLocation()
{
	if( TargetMan && !TargetMan->IsPendingKill())
	{
		EndPos = TargetMan->GetActorLocation();
		NiagaraComp->SetVectorParameter(TEXT("User.BeamEnd"),EndPos);
	}
}

void ATLaserBeam::SetDamage(float NewDamage)
{
	Damage = NewDamage;
}

ATManBase* ATLaserBeam::GetTargetMan() const
{
	return TargetMan;
}

