// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/THeroSkill.h"

#include "Character/THero.h"
#include "Kismet/GameplayStatics.h"

void UTHeroSkill::Execute(UWorld* World)
{
	Super::Execute(World);

	if( Hero) return ;
	
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(this,ATHero::StaticClass(),Actors);
	if( Actors.Num())
	{
		Hero = Cast<ATHero>(Actors[0]);
	}
}

void UTHeroSkill::ExactlyExecute()
{
	Hero->OnManReborn();
}

void UTHeroSkill::OnCoolDownUpdate()
{
	Super::OnCoolDownUpdate();
	if( bCanUse)
	{
		ExactlyExecute();
	}
}
