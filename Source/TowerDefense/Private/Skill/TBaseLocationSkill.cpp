// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/TBaseLocationSkill.h"

#include "GamePlay/TPlayerController.h"
#include "Kismet/GameplayStatics.h"

void UTBaseLocationSkill::Execute(UWorld* World)
{
	Super::Execute(World);
	ATPlayerController* PC = Cast<ATPlayerController>(UGameplayStatics::GetPlayerController(World,0));
	if( ensureMsgf(PC,TEXT("Fail to Use SKill, ATPlayerController is Null")))
	{
		SpawnLocation = PC->GetCursorHitLoc();
	}
}
