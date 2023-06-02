// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/TBaseDialogItem.h"

#include "Component/ActorComp/TUIManagerComponent.h"
#include "Component/ActorComp/Player/TDialogComponent.h"
#include "Kismet/GameplayStatics.h"

void ATBaseDialogItem::Interact_Implementation(APawn* InstigatorPawn)
{
	Super::Interact_Implementation(InstigatorPawn);
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if( PC)
	{
		UTDialogComponent* DLMgr = Cast<UTDialogComponent>(PC->GetComponentByClass(UTDialogComponent::StaticClass()));
		if( DLMgr)
		{
			DLMgr->TriggerDialog(this->DialogTable);
		}
	}
}
