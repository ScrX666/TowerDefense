// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/TGameInstance.h"

#include "MoviePlayer.h"
#include "Blueprint/UserWidget.h"
#include "Components/Widget.h"
#include "GamePlay/TDataTableManager.h"
#include "Kismet/GameplayStatics.h"

/*
 * 添加能够建造的塔
 */
bool UTGameInstance::AddTower(TSubclassOf<ATMainTower> Tower)
{
	if( OwnTowers.Contains(Tower)) return false;
	OwnTowers.Add(Tower);
	return true;
}
/*
 * 获取所有能够建造的塔
 */
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

	TowerAttackRangeAmend = TDataTableManager::GetInstance()->GetLevelInfo(
		FName(UGameplayStatics::GetCurrentLevelName(this, true))).TowerAttackRangeAmend;
	
	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UTGameInstance::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UTGameInstance::EndLoadingScreen);
}

void UTGameInstance::BeginLoadingScreen(const FString& MapName)
{
	if (!IsRunningDedicatedServer())
	{
		LoadNum++;
		
		if (LoadNum == 1) return;

		// 获取loading界面信息
		LoadingTexture = TDataTableManager::GetInstance()->GetLevelInfo(
			FName(UGameplayStatics::GetCurrentLevelName(this, true)))
		.ChangeLevelTexture;
		LoadingText = TDataTableManager::GetInstance()->GetLevelInfo(
			FName(UGameplayStatics::GetCurrentLevelName(this, true)))
		.ChangeLevelText;
		
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

		LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
		LoadingScreen.bMoviesAreSkippable = true;
		LoadingScreen.PlaybackType = EMoviePlaybackType::MT_Looped;
		// LoadingScreen.MoviePaths.Add("Test");

		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}
}
 
void UTGameInstance::EndLoadingScreen(UWorld* World)
{
	GEngine->AddOnScreenDebugMessage(1,20,FColor::Red,TEXT("EndLoadingScreen"));
}
