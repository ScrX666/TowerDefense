// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ActorComp/TSoundManagerComponent.h"

#include "Components/AudioComponent.h"
#include "GamePlay/TDataTableManager.h"
#include "GamePlay/TGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTSoundManagerComponent::UTSoundManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	BackgroundSoundComp = CreateDefaultSubobject<UAudioComponent>(TEXT("BackgroundSoundComp"));
	AmbientSoundComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AmbientSoundComp"));

	MusicVolume = 1.0f;
	SoundVolume = 1.0f;
}

void UTSoundManagerComponent::SetBgAndAmSound(USoundBase* AmSound, USoundBase* BGSound)
{
	AmbientSound = AmSound;
	BackgroundSound = BGSound;
}

void UTSoundManagerComponent::PlayAmbientSound()
{
	AmbientSoundComp->SetSound(AmbientSound);
	AmbientSoundComp->SetVolumeMultiplier(MusicVolume);
	AmbientSoundComp->Play();
}

void UTSoundManagerComponent::PlayBackgroundSound()
{
	BackgroundSoundComp->SetSound(BackgroundSound);
	BackgroundSoundComp->SetVolumeMultiplier(MusicVolume);
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

void UTSoundManagerComponent::OnBtnClick()
{
	UGameplayStatics::PlaySound2D(this,UIClickSound,SoundVolume);
}

/*
 * 游戏结束播放音效，通过委托触发
 */
void UTSoundManagerComponent::OnGameEnd(bool bIsWin)
{
	if( bIsWin)
	{
		UGameplayStatics::PlaySound2D(this, WinGameSound,SoundVolume);
	}
	else
	{
		UGameplayStatics::PlaySound2D(this,FailGameSound,SoundVolume);
	}
	UTGameInstance* GameInstance = Cast<UTGameInstance>(UGameplayStatics::GetGameInstance(this));
	if( GameInstance)
	{
		GameInstance->MusicVolume = MusicVolume;
		GameInstance->SoundVolume = SoundVolume;
	}
}
/*
 * 创建删除塔播放音效，通过委托触发
 */
void UTSoundManagerComponent::OnConstructTowerBulid(ATMainTower* Tower, bool bIsConstruct)
{
	if( bIsConstruct)
	{
		UGameplayStatics::PlaySound2D(this, BuildSound,SoundVolume);
	}
	else
	{
		UGameplayStatics::PlaySound2D(this, DestorySound,SoundVolume);
	}
}

void UTSoundManagerComponent::SetMusicVolume(float NewVolume)
{
	MusicVolume = NewVolume;
	AmbientSoundComp->SetVolumeMultiplier(MusicVolume);
	BackgroundSoundComp->SetVolumeMultiplier(MusicVolume);
}

void UTSoundManagerComponent::SetSoundVolume(float NewVolume)
{
	SoundVolume = NewVolume;
}


// Called when the game starts
void UTSoundManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UTGameInstance* GameInstance = Cast<UTGameInstance>(UGameplayStatics::GetGameInstance(this));
	if( GameInstance)
	{
		SetMusicVolume(GameInstance->MusicVolume);
		SetSoundVolume(GameInstance->SoundVolume);
	}

	
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

