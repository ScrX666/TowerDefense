// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ActorComp/Player/TDialogComponent.h"
#include "Component/ActorComp/TUIManagerComponent.h"
#include "GamePlay/TDataTableManager.h"
#include "GamePlay/TUIState.h"
#include "Kismet/GameplayStatics.h"
#include "TowerDefense/TowerDefenseGameModeBase.h"

// Sets default values for this component's properties
UTDialogComponent::UTDialogComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTDialogComponent::BeginPlay()
{
	Super::BeginPlay();

	// 关卡前开始对话
	UDataTable* BeginDialog = TDataTableManager::GetInstance()->GetLevelInfo(
		FName(UGameplayStatics::GetCurrentLevelName(this, true))
	).BeginDialogTable;
	if( BeginDialog == nullptr)
	{
		ATowerDefenseGameModeBase* TDGameMode = Cast<ATowerDefenseGameModeBase>(UGameplayStatics::GetGameMode(this));
		if( TDGameMode)
		TDGameMode->GameStart();
	}
	else
	{
		TriggerDialog(BeginDialog);
	}
	
	
}


/*
 * 执行可交互对象的对话
 */
void UTDialogComponent::ExecuteDialogEvent(TSubclassOf<UObject> DialogEventCla)
{
	if( *DialogEventCla == nullptr)
	{
		UE_LOG(LogTemp,Log,TEXT("The class is empty"));
		return ;
	}
	if( !DialogEventCla->ImplementsInterface(UTDialogEventInterface::StaticClass()))
	{
		UE_LOG(LogTemp,Error,TEXT("The class dont implement dialogevent interface"));
		return ;
	}
	
	if( !DialogEvents.Contains(DialogEventCla))
	{
		DialogEvents.Add(DialogEventCla,NewObject<UObject>(this,DialogEventCla));
	}
	ITDialogEventInterface::Execute_TriggerDialogEvent(DialogEvents[DialogEventCla].GetObject(),GetWorld());
}
/*
 * 触发对话
 */
void UTDialogComponent::TriggerDialog(UDataTable* DialogTable)
{
	CurDialogTable = DialogTable;
	
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if( PC)
	{
		UTUIManagerComponent* UIMgr = Cast<UTUIManagerComponent>(PC->GetComponentByClass(UTUIManagerComponent::StaticClass()));
		if( UIMgr)
		{
			if( DialogTable)
				UIMgr->PushUIState(TEXT("DialogPanel"));
		}
	}
}

