// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/TBaseLocationSkill.h"

#include "BlueprintFunctionLibrary/TBlueprintFunctionLibrary.h"
#include "Component/ActorComp/TMouseControlComponent.h"
#include "GamePlay/TPlayerController.h"
#include "Kismet/GameplayStatics.h"

void UTBaseLocationSkill::Execute(UWorld* World)
{
	Super::Execute(World);
	ATPlayerController* PC = Cast<ATPlayerController>(UGameplayStatics::GetPlayerController(World,0));
	if( ensureMsgf(PC,TEXT("Fail to Use SKill, ATPlayerController is Null")))
	{
		SkillLocation = PC->MouseControlComponent->GetCursorHitLoc();
	}
	UTBlueprintFunctionLibrary::PlayRandomSound(World,SkillSounds,SkillLocation);
}
