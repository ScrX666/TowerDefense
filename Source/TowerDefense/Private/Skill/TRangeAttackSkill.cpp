// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/TRangeAttackSkill.h"

#include "DrawDebugHelpers.h"
#include "NiagaraFunctionLibrary.h"
#include "Character/TEnemyBase.h"
#include "Kismet/GameplayStatics.h"

void UTRangeAttackSkill::Execute(UWorld* World)
{
	Super::Execute(World);

	// 范围检测
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);
	
	FVector End = FVector(0.0f,0.0f,10.0f) + SkillLocation;
	FVector Start = FVector(0.0f,0.0f,-10.0f) + SkillLocation;
	
	float SphereRadius = SkillRange;
	TArray<FHitResult> Hits;
	FCollisionShape Shape;
	Shape.SetSphere(SphereRadius);
	bool bBlockHit = GetWorld()->SweepMultiByObjectType(Hits,Start, End, FQuat::Identity,ObjectQueryParams,Shape);
	FColor Color = bBlockHit ? FColor::Red : FColor::Green;

	// 给予伤害
	for( FHitResult HitResult : Hits)
	{
		AActor* HitActor = HitResult.GetActor();
		if( HitActor)                                                   
		{                                                               
			if( HitActor->IsA<ATEnemyBase>())            
			{
				UGameplayStatics::ApplyDamage(HitActor,Damage,nullptr,nullptr,UDamageType::StaticClass());
			}                                                           
		}
	}
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			World,
			NiagaraSystem,
			SkillLocation,
			FRotator::ZeroRotator,
			FVector::OneVector);

	
	DrawDebugSphere(GetWorld(),SkillLocation,SphereRadius,32,Color,false,2.0f);
}
