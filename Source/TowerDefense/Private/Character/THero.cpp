// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/THero.h"

#include "NiagaraComponent.h"
#include "AI/Hero/THeroController.h"
#include "Components/CapsuleComponent.h"

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
