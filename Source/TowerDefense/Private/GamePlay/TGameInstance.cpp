// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/TGameInstance.h"

#include "MoviePlayer.h"
#include "Blueprint/UserWidget.h"
#include "Components/Widget.h"
#include "GamePlay/TPlayerController.h"
#include "Kismet/GameplayStatics.h"


bool UTGameInstance::AddTower(TSubclassOf<ATMainTower> Tower)
{
	if( OwnTowers.Contains(Tower)) return false;
	OwnTowers.Add(Tower);
	return true;
}

const TArray<TSubclassOf<ATMainTower>>& UTGameInstance::GetOwnTowers()
{
	if( OwnTowers.Num() == 0)
	{
		for( TSubclassOf<ATMainTower>& Tower : InitTowers)
		{
			OwnTowers.AddUnique(Tower);
		}
	}
	return OwnTowers;
}

void UTGameInstance::Init()
{
	Super::Init();

	
	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UTGameInstance::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UTGameInstance::EndLoadingScreen);
}

void UTGameInstance::BeginLoadingScreen(const FString& MapName)
{
	if (!IsRunningDedicatedServer())
	{
		FLoadingScreenAttributes LoadingScreen;
		
		
		APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
		if(PC)
		{
			UUserWidget* LoadingUI = CreateWidget<UUserWidget>(PC, LoadingUICla);
			if( LoadingUI)
				LoadingScreen.WidgetLoadingScreen =  LoadingUI->TakeWidget();
			else
			{
				LoadingScreen.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();
			}
		}
		else
		{
			LoadingScreen.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();
		}
		UE_LOG(LogTemp, Log, TEXT("beginloadMap"));

		// loadNum++;
		//
		// if (loadNum == 1) return;

		LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
		LoadingScreen.bMoviesAreSkippable = true;
		LoadingScreen.PlaybackType = EMoviePlaybackType::MT_Looped;
		LoadingScreen.MoviePaths.Add("Test");

		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}
}
 
void UTGameInstance::EndLoadingScreen(UWorld* World)
{
	UE_LOG(LogTemp, Log, TEXT("EndLoadingScreen"));
}
