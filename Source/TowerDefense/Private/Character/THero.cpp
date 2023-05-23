// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/THero.h"

#include "NiagaraComponent.h"
#include "AI/Hero/THeroController.h"
#include "Component/ActorComp/TManStateAndBuffer.h"
#include "Components/CapsuleComponent.h"
#include "GamePlay/TPlayerController.h"
#include "Kismet/GameplayStatics.h"

ATHero::ATHero()
{
	SelectedEffect = CreateDefaultSubobject<UNiagaraComponent>("SelectedEffect");
	SelectedEffect->SetupAttachment(RootComponent);
	AIControllerClass = ATHeroController::StaticClass();
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Hero"));
}

void ATHero::OnSelected(bool bIsSelected)
{
	Super::OnSelected(bIsSelected);
	if( bIsSelected)
	{
		SelectedEffect->SetHiddenInGame(false);
		SelectedEffect->Activate(true);
	}
	else
	{
		SelectedEffect->SetHiddenInGame(true);
	}
	OnSelectHero.Broadcast(bIsSelected);
}

void ATHero::OnManDead()
{
	SetActorHiddenInGame(true);
	ATPlayerController* PC = Cast<ATPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	ManAIC->DisableSolo(nullptr);
	if( PC)
	{
		PC->ExecuteSkill(TEXT("Hero"));
		PC->ConfirmExecuteSkill();
	}
}

void ATHero::OnManReborn()
{
	SetActorHiddenInGame(false);
	// 回复生命
	ManStateAndBuffer->ApplyHealthChange(nullptr,ManStateAndBuffer->ManState.MaxHealth);
	// 复活后手动更新被感知的敌人
	ManualPerceptionUpdated();
}
