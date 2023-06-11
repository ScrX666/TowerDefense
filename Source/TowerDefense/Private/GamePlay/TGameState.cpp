// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/TGameState.h"

#include "AI/TSplineMapActor.h"
#include "Building/TPathEndBuilding.h"
#include "GamePlay/TPlayerController.h"
#include "GamePlay/TPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "TowerDefense/TowerDefenseGameModeBase.h"

void ATGameState::BeginPlay()
{
	Super::BeginPlay();

	// 获取所有的敌人生成器
	TArray<AActor*> Out;
	UGameplayStatics::GetAllActorsOfClass(this, ATSplineMapActor::StaticClass(),Out);
	for( auto const Actor : Out)
	{
		EnemySpawners.Add(Cast<ATSplineMapActor>(Actor));
	}
	
}
void ATGameState::OnEnemyNumChange(int32 Change)
{
	CurrentExistEnemyCount += Change;
	// 防止游戏结束 现存敌人销毁，引起的空指针引用
	if(!Cast<ATPlayerController>(UGameplayStatics::GetPlayerController(this,0)) ||
		Cast<ATowerDefenseGameModeBase>(UGameplayStatics::GetGameMode(this))->bGameEnd)
			return ;
	
	ATPlayerState* PlayerState = Cast<ATPlayerController>(UGameplayStatics::GetPlayerController(this,0))->TPlayerState;

	if( !PlayerState || !PlayerState->EndBuilding) return ;
	
	if( CurrentExistEnemyCount <= 0 && IsFinishSpawn() && !PlayerState->EndBuilding->IsDead())
	{
		Cast<ATowerDefenseGameModeBase>(UGameplayStatics::GetGameMode(this))->OnGameEnd.Broadcast(true);
		PlayerState->AllEnemyDead = true;
	}
}

bool ATGameState::IsFinishSpawn() const
{
	for( auto const Spanwer : EnemySpawners)
	{
		if( Spanwer)
		{
			if( Spanwer->bFinishSpawn == false) return false;
		}
	}
	return true;
}

