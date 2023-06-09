// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ActorComp/Tower/TAttackHandleComponent.h"

#include "Building/Tower/TMainTower.h"
#include "Character/TEnemyBase.h"
#include "Character/TManBase.h"

// Sets default values for this component's properties
UTAttackHandleComponent::UTAttackHandleComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	ParallelAttackCount = 1;
	SetParallelAttackCount(ParallelAttackCount);
}

void UTAttackHandleComponent::AttackTargetIn(ATManBase* Man)
{
	auto OthMan = Cast<ATEnemyBase>(Man);
	if( OthMan != nullptr &&
		TargetIsFull() == false)
	{
		if( TargetIsEmpty())
		{
			AddTarget(OthMan);
			OwnTower->TargetInRange();
		}
		else
		{
			AddTarget(OthMan);
		}
	}
}

void UTAttackHandleComponent::AttackTargetOut(ATManBase* Man)
{
	if( Man == nullptr || Man->IsA<ATEnemyBase>() == false) return ;
	
	RemoveAttackTarget(Cast<ATManBase>(Man));
		
	TArray<AActor*> ManBases;
	OwnTower->GetOverlappingActors(ManBases, ATEnemyBase::StaticClass());
	if( ManBases.Num() == 0 && TargetIsEmpty())
	{
		// TargetMan = nullptr;
		OwnTower->NoTargetInRange();
	}
	else
	{
		// UE_LOG(LogTemp,Log,TEXT("AttackRangeEndOverlap Man NUM %d"),ManBases.Num());
		// UE_LOG(LogTemp,Log,TEXT("AttackHandleComponent->TargetIsFull %d"),TargetIsFull());
			
			
		// 添加敌人，可能重复添加，所以循环判断
		if( TargetIsFull() == false)
		{
			for( int i = 0; i < ManBases.Num(); i++)
			{
				if( !ExistInAttackTarget(Cast<ATManBase>(ManBases[i]))
					&& AddTarget(Cast<ATManBase>(ManBases[i])))
						break;
			}
			
			OwnTower->TargetInRange();
		}
	}
}

/*
 * 能够攻击的敌人数量是否已经满了
 */
bool UTAttackHandleComponent::TargetIsFull()
{
	for( int i = 0; i < ParallelAttackCount; i++)
	{
		const ATManBase* Man = TargetMans[i];
		if( IsValid(Man) == false) return false;
	}
	return true;
}

bool UTAttackHandleComponent::TargetIsEmpty()
{
	for( int i = 0; i < ParallelAttackCount; i++)
	{
		const ATManBase* Man = TargetMans[i];
		if( IsValid(Man) == true) return false;
	}
	return true;
}

/*
 * 添加敌人
 */
bool UTAttackHandleComponent::AddTarget(ATManBase* ManBase)
{
	// if( TargetMans.Contains(ManBase)) return false;
	for( int i = 0; i < ParallelAttackCount; i++)
	{
		const ATManBase* Man = TargetMans[i];
		// std::unique_lock<std::mutex> lock(AddMutex);
		if( IsValid(Man) == false)
		{ 
			TargetMans[i] = ManBase;
			UE_LOG(LogTemp,Warning,TEXT("Add AttackTarget Success"));
			return true;
		}
		if( TargetMans[i] == ManBase)
		{
			break;
		}
	}
	UE_LOG(LogTemp,Warning,TEXT("Add AttackTarget Failure"));
	return false;
}
/*
 * 设置并行攻击数量
 */
void UTAttackHandleComponent::SetParallelAttackCount(int32 NewCount)
{
	ParallelAttackCount = NewCount;
	int32 CurrentCount = TargetMans.Num();
	if( NewCount > CurrentCount)
	{
		// 添加
		while(NewCount > CurrentCount)
		{
			TargetMans.Add(nullptr);
			NewCount--;
		}
	}
	else
	{
		// 删除
		while(NewCount < CurrentCount)
		{
			TargetMans.RemoveAt(TargetMans.Num() - 1);
			CurrentCount--;
		}
	}
}

int32 UTAttackHandleComponent::GetParallelAttackCount() const
{
	return ParallelAttackCount;
}

/*
 * 获取攻击对象
 */
ATManBase* UTAttackHandleComponent::GetAttackTarget(int32 Index)
{
	return TargetMans[Index];
}
/*
 * 移除攻击对象
 */
void UTAttackHandleComponent::RemoveAttackTarget(const ATManBase* RemoveMan)
{
	for( int i = 0; i < ParallelAttackCount; i++)
	{
		if(TargetMans[i] == RemoveMan)
		{
			TargetMans[i] = nullptr;
		}
	}
}

bool UTAttackHandleComponent::ExistInAttackTarget(const ATManBase* TargetMan) const
{
	return TargetMans.Contains(TargetMan);
}

FVector UTAttackHandleComponent::ReturnTargetLocation() const
{
	for( int i = 0; i < ParallelAttackCount; i++)
	{
		const ATManBase* Man = TargetMans[i];
		if( IsValid(Man) == true)
		{
			return Man->GetActorLocation();
		}
	}
	return FVector::ZeroVector;
}


// Called when the game starts
void UTAttackHandleComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnTower = Cast<ATMainTower>(GetOwner());	
}