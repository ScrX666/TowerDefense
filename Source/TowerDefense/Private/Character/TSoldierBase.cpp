// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TSoldierBase.h"

void ATSoldierBase::OnConstruct(ATMainAttachBase* AttachBase)
{
	// if( AttachBase == nullptr)
	// {
	// 	UE_LOG(LogTemp,Log,TEXT("AttachBase Null"));
	// 	AttackRangeMesh->SetVisibility(true);
	// 	// 动态设置攻击范围显示
	// 	//AttackRangeMesh->SetWorldScale3D(FVector(AttackRange / 200.0f,AttackRange / 200.0f,1));
	// 	UpdateAttackRange(AttackRange);
	// 	return ;
	// }
	// else
	// {
	// 	UE_LOG(LogTemp,Log,TEXT("AttachBase Not Null"));
	//
	// 	AttackRangeMesh->SetVisibility(false);
	// 	AttackRangeSphere->OnComponentBeginOverlap.AddDynamic(this, &ATMainTower::AttackRangeOverlap);
	// 	AttackRangeSphere->OnComponentEndOverlap.AddDynamic(this, &ATMainTower::AttackRangeEndOverlap);
	//
	// 	//生成时 函数还没有绑定，TargetMan 没有指定，手动触发一次
	// 	AttackRangeSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// 	AttackRangeSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	// 	return;
	// }
}

void ATSoldierBase::OnDestory()
{
}

void ATSoldierBase::OnHovered(bool bHovered)
{
}

void ATSoldierBase::OnSelected(bool bIsSelected)
{
}

void ATSoldierBase::CanConstructBuilding(bool bCanConstruct)
{
	if( bCanConstruct)
	{
		ChangeMaterial(TEXT("CanConstruct"));
	}
	else
	{
		ChangeMaterial(TEXT("NoConstruct"));
	}
}

int32 ATSoldierBase::GetCostCoins()
{
	return 10;
}

void ATSoldierBase::ChangeMaterial(FName MatName)
{
	if( Materials.Num() == 0)
	{
		UE_LOG(LogTemp,Warning,TEXT("Materials None"));
		return ;
	}
	
	UMaterialInterface* Material = *Materials.Find(MatName);
	if( Material != nullptr)
	{
		TArray<USceneComponent*> OutChildren;
		RootComponent->GetChildrenComponents(true, OutChildren);
		if( RootComponent != nullptr) OutChildren.Add(RootComponent);
		for( const auto Comp : OutChildren)
		{
			if( Comp->IsA<UMeshComponent>())
			{
				UMeshComponent* CurMesh = Cast<UMeshComponent>(Comp);
				const int MaterialCount = CurMesh->GetMaterials().Num();
				for( int i = 0; i < MaterialCount; ++i)
				{
					CurMesh->SetMaterial(i, Material);
				}
			}
		}
		GetMesh()->SetMaterial(0,Material);
	}
}