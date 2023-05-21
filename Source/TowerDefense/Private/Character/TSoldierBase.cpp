// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TSoldierBase.h"

#include "Character/TEnemyBase.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ATSoldierBase::ATSoldierBase()
{
	Tags.Add(TEXT("Soldier"));
	AttackManCla = ATEnemyBase::StaticClass();
}

void ATSoldierBase::OnConstruct(ATMainAttachBase* AttachBase)
{
	PerceptionComponent->SetSenseEnabled(UAISenseConfig_Sight::StaticClass(),false);
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