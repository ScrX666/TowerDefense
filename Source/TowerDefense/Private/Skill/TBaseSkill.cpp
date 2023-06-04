// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/TBaseSkill.h"

/*
 * 释放技能
 */
void UTBaseSkill::Execute(UWorld* World)
{
	if( bCanUse == false) return;
	// 子类实现 具体攻击逻辑

	this->CurWorld = World;
	// 定时
	CurrentCoolDown = 0.0f;
	bCanUse = false;
	GetWorld()->GetTimerManager().SetTimer(CoolDownHandle,this,&UTBaseSkill::OnCoolDownUpdate,0.1f,true);
}

void UTBaseSkill::Init(UWorld* World)
{
}

/*
 * 更新技能状态 定时调用
 */
void UTBaseSkill::OnCoolDownUpdate()
{
	CurrentCoolDown += 0.1f;
	if( CurrentCoolDown >= SkillCoolDown)
	{
		bCanUse = true;
		GetWorld()->GetTimerManager().ClearTimer(CoolDownHandle);
	}
	OnCDUpdate.Broadcast(CurrentCoolDown,SkillCoolDown,bCanUse);
}
