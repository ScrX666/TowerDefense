// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ActorComp/TSoundManagerComponent.h"

#include "Components/AudioComponent.h"
#include "GamePlay/TDataTableManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTSoundManagerComponent::UTSoundManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	BackgroundSoundComp = CreateDefaultSubobject<UAudioComponent>(TEXT("BackgroundSoundComp"));
	AmbientSoundComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AmbientSoundComp"));
}

void UTSoundManagerComponent::SetBgAndAmSound(USoundBase* AmSound, USoundBase* BGSound)
{
	AmbientSound = AmSound;
	BackgroundSound = BGSound;
}

void UTSoundManagerComponent::PlayAmbientSound()
{
	AmbientSoundComp->SetSound(AmbientSound);
	AmbientSoundComp->Play();
}

void UTSoundManagerComponent::PlayBackgroundSound()
{
	BackgroundSoundComp->SetSound(BackgroundSound);
	BackgroundSoundComp->Play();
}

void UTSoundManagerComponent::PlayHeroClickSound()
{
	UGameplayStatics::PlaySound2D(this,ClickHeroSound);
}

void UTSoundManagerComponent::OnSelectHero(bool bIsSelected)
{
	if( bIsSelected)
	{
		PlayHeroClickSound();
	}
}

void UTSoundManagerComponent::OnGameEnd(bool bIsWin)
{
	if( bIsWin)
	{
		UGameplayStatics::PlaySound2D(this, WinGameSound);
	}
	else
	{
		UGameplayStatics::PlaySound2D(this,FailGameSound);
	}
}


// Called when the game starts
void UTSoundManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	auto LevelInfo = TDataTableManager::GetInstance()->GetLevelInfo(FName(UGameplayStatics::GetCurrentLevelName(this)));
	SetBgAndAmSound(LevelInfo.AmbientSound,LevelInfo.BackgroundMusic);
	PlayBackgroundSound();
	PlayAmbientSound();
}


// Called every frame
void UTSoundManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

