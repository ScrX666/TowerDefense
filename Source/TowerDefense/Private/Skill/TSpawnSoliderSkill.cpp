// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/TSpawnSoliderSkill.h"

#include "Character/THero.h"
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
		SpawnLoc.X += FMath::RandRange(-RandomRange,RandomRange);
		SpawnLoc.Y += FMath::RandRange(-RandomRange,RandomRange);
		SpawnLoc.Z += 40.0f;
		FRotator SpawnRot = FRotator::ZeroRotator;
		SpawnRot.Yaw = FMath::RandRange(0.0f,360.0f);
		FTransform SpawnTransform(SpawnRot,SpawnLoc,FVector(SoliderScale));
		if( SoliderCla)
		{
			World->SpawnActor(SoliderCla,&SpawnTransform,ActorSpawnParameters);
		}
	}
}

void UTSpawnSoliderSkill::Init(UWorld* World)
{
	Super::Init(World);
	AActor* Hero = UGameplayStatics::GetActorOfClass(World,ATHero::StaticClass());
	if( Hero)
	{
		SoliderScale = Hero->GetActorScale().X;
	}
}
