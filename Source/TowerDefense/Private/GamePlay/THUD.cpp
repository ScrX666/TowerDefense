// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/THUD.h"


#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "TowerDefense/TowerDefenseGameModeBase.h"

void ATHUD::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp,Log,TEXT("ATHUD BeginPlay"));
	// auto TDGameMode = Cast<ATowerDefenseGameModeBase>(UGameplayStatics::GetGameMode(this));
	// // 绑定 结束游戏事件
	//
	// TDGameMode->OnGameEnd.AddDynamic(this, &ATHUD::ShowEndGamePanel);
}

void ATHUD::Exit()
{
	UKismetSystemLibrary::QuitGame(this, UGameplayStatics::GetPlayerController(this, 0),EQuitPreference::Quit,true);
}

void ATHUD::ShowEndGamePanel(bool IsWin)
{
	UE_LOG(LogTemp,Log,TEXT("End Game"));
	EndGamePanel = CreateWidget(GetWorld(), EndGamePanelClass);
	if( EndGamePanel)
	{
		EndGamePanel->AddToViewport();
		auto TextBlock = Cast<UTextBlock>(EndGamePanel->GetWidgetFromName(TEXT("T_Tips")));
		if( TextBlock)
		{
			FString Text = TEXT("Lose Game");
			
			if( IsWin)
			{
				Text = TEXT("Win Game");
			}
			UE_LOG(LogTemp,Log,TEXT("ShowEndGamePanel Game"));
			TextBlock->SetText(FText::FromString(Text));
		}
		auto Button = Cast<UButton>(EndGamePanel->GetWidgetFromName(TEXT("BTN_Exit")));
		if( Button)
		{
			FScriptDelegate ButtonDelegate;
			ButtonDelegate.BindUFunction(this,"Exit");
			Button->OnReleased.Add(ButtonDelegate);
		}
	}
	else
	{
		UE_LOG(LogTemp,Log,TEXT("EndGamePanel NULL"));
	}
}