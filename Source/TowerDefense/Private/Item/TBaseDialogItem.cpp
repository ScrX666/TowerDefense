// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/TBaseDialogItem.h"

#include "Component/ActorComp/TUIManagerComponent.h"
#include "Kismet/GameplayStatics.h"

void ATBaseDialogItem::Interact_Implementation(APawn* InstigatorPawn)
{
	Super::Interact_Implementation(InstigatorPawn);
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if( PC)
	{
		UTUIManagerComponent* UIMgr = Cast<UTUIManagerComponent>(PC->GetComponentByClass(UTUIManagerComponent::StaticClass()));
		if( UIMgr)
		{
			UIMgr->DialogTable = DialogTable;
			if( DialogTable)
			UIMgr->PushUIState(TEXT("DialogPanel"));
		}
	}
}
