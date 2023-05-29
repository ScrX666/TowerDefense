// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/TSpawnSoliderSkill.h"

#include "GamePlay/TPlayerController.h"
#include "Kismet/GameplayStatics.h"

void UTSpawnSoliderSkill::Execute(UWorld* World)
{
	if( bCanUse == false) return;
	Super::Execute(World);
	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	for( int32 i = 0; i < SpawnCount; i++)
	{
		FVector SpawnLoc = SkillLocation;
		SpawnLoc.X += FMath::RandRange(-50.0f,50.0f);
		SpawnLoc.Y += FMath::RandRange(-50.0f,50.0f);
		SpawnLoc.Z += 20.0f;
		FRotator SpawnRot = FRotator::ZeroRotator;
		SpawnRot.Yaw = FMath::RandRange(0.0f,360.0f);
		if( SoliderCla)
		{
			World->SpawnActor(SoliderCla,&SpawnLoc,&SpawnRot,ActorSpawnParameters);
		}
	}
}
