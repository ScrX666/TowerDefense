// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ActorComp/TSkillManagerComponent.h"

#include "Skill/TBaseSkill.h"

// Sets default values for this component's properties
UTSkillManagerComponent::UTSkillManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}
/*
 * 获取技能
 */
UTBaseSkill* UTSkillManagerComponent::GetSkill(FName SkillName)
{
	if( SkillsWithName.Contains(SkillName))
	{
		return SkillsWithName[SkillName];
	}
	// 没有技能 但有技能的类，就创建技能
	if( SkillsCla.Contains(SkillName) && SkillsCla[SkillName])
	{
		UTBaseSkill* Skill = NewObject<UTBaseSkill>(this,SkillsCla[SkillName]);
		SkillsWithName.Add(SkillName,Skill);
		return SkillsWithName[SkillName];
	}
	return nullptr;
}
/*
 * 获取所有技能
 */
TArray<FName>& UTSkillManagerComponent::GetAllSkill()
{
	if( SkillsWithName.Num() == 0)
	{
		for( auto& SkillCla : SkillsCla)
		{
			SkillsNameInArray.Add(SkillCla.Key);
		}
	}
	
	return SkillsNameInArray;
}
/*
 * 执行技能
 */
bool UTSkillManagerComponent::Execute(FName SkillName)
{
	if( SkillsWithName.Contains(SkillName))
	{
		SkillsWithName[SkillName]->Execute(GetWorld());
		return true;
	}
	// 没有技能 但有技能的类，就创建技能
	if( SkillsCla.Contains(SkillName) && SkillsCla[SkillName])
	{
		UTBaseSkill* Skill = NewObject<UTBaseSkill>(this,SkillsCla[SkillName]);
		SkillsWithName.Add(SkillName,Skill);
		SkillsWithName[SkillName]->Execute(GetWorld());
		return true;
	}
	UE_LOG(LogTemp,Error,TEXT("Dont exist %s"),*SkillName.ToString());
	return false;
}


// Called when the game starts
void UTSkillManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTSkillManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

