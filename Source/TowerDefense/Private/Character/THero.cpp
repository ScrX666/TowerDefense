// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/THero.h"

#include "NiagaraComponent.h"
#include "AI/Hero/THeroController.h"
#include "BlueprintFunctionLibrary/TBlueprintFunctionLibrary.h"
#include "Component/ActorComp/TManStateAndBuffer.h"
#include "Component/ActorComp/TMouseControlComponent.h"
#include "Component/ActorComp/TSkillManagerComponent.h"
#include "Components/CapsuleComponent.h"
#include "GamePlay/TPlayerController.h"
#include "Kismet/GameplayStatics.h"

ATHero::ATHero()
{
	SelectedEffect = CreateDefaultSubobject<UNiagaraComponent>("SelectedEffect");
	SelectedEffect->SetupAttachment(RootComponent);
	WeaponMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMeshComp");
	WeaponMeshComp->SetupAttachment(RootComponent);
	WeaponMeshComp->SetCollisionProfileName(TEXT("NoCollision"));
	WeaponMeshComp->SetHiddenInGame(true);
	
	AIControllerClass = ATHeroController::StaticClass();
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Hero"));
}

void ATHero::OnSelected(bool bIsSelected)
{
	Super::OnSelected(bIsSelected);
	if( bIsSelected)
	{
		SelectedEffect->SetHiddenInGame(false);
		SelectedEffect->Activate(true);
	}
	else
	{
		SelectedEffect->SetHiddenInGame(true);
	}
	OnSelectHero.Broadcast(bIsSelected);
}

void ATHero::OnManDead()
{
	SetActorHiddenInGame(true);
	ManAIC->RunBehaviorTree(nullptr);
	ATPlayerController* PC = Cast<ATPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	ManAIC->DisableSolo(nullptr);
	if( PC)
	{
		// PC->MouseControlComponent->ExecuteSkill(TEXT("Hero"));
		PC->SkillManagerComponent->Execute(TEXT("Hero"));
		// PC->MouseControlComponent->ConfirmExecuteSkill();
	}
}

void ATHero::OnManReborn()
{
	ManAIC->RunBehaviorTree(ManAIC->BehaviorTree);
	SetActorHiddenInGame(false);
	// 回复生命
	ManStateAndBuffer->ApplyHealthChange(nullptr,ManStateAndBuffer->ManState.MaxHealth);
	// 复活后手动更新被感知的敌人
	ManualPerceptionUpdated();

	UTBlueprintFunctionLibrary::PlayRandomSound(this,RebornSounds,this->GetActorLocation());
}

void ATHero::BeginPlay()
{
	Super::BeginPlay();

	// 绑定武器
	FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::KeepWorld,false);
	AttachmentTransformRules.LocationRule = EAttachmentRule::SnapToTarget;
	WeaponMeshComp->AttachToComponent(GetMesh(),AttachmentTransformRules,TEXT("RightHandIndex4Socket"));
}
