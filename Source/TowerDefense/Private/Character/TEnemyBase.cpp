// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TEnemyBase.h"

#include "AI/Enemy/TEnemyAIController.h"
#include "Character/TSoldierBase.h"

ATEnemyBase::ATEnemyBase()
{
	Tags.Add(TEXT("Enemy"));
	AttackManCla = ATSoldierBase::StaticClass();
	AIControllerClass = ATEnemyAIController::StaticClass();
}
