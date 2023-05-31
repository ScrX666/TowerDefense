// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/TBTServiceCheckAttackInRange.h"

#include "AI/TAIBaseController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UTBTServiceCheckAttackInRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if( ensure(BlackboardComponent))
	{
		AActor* TargetActor = Cast<AActor>(BlackboardComponent->GetValueAsObject(TEXT("TargetActor")));
		if( TargetActor)
		{
			AAIController* Controller = Cast<AAIController>(OwnerComp.GetAIOwner());
			if( ensure(Controller))
			{
				APawn* Pawn = Controller->GetPawn();
				if( ensure(Pawn))
				{
					FVector TargetLoc = TargetActor->GetActorLocation();
					FVector PawnLoc = Pawn->GetActorLocation();
					TargetLoc.Z = 0.0f;
					PawnLoc.Z = 0.0f;
					float DistanceTo = FVector::Distance(TargetLoc,PawnLoc);

					float RangeScale = FMath::Max(Pawn->GetActorScale().X,TargetActor->GetActorScale().X);
					
					bool bWithInRange = DistanceTo < AttackRange * RangeScale;
					UE_LOG(LogTemp,Log,TEXT("bWithInAttackRange %d"),bWithInRange);
					UE_LOG(LogTemp,Log,TEXT("DistanceTo %f"),DistanceTo);
					// bool bHasLos = false;
					// if( bWithInRange)
					// {
					// 	bHasLos = Controller->LineOfSightTo(TargetActor);
					// 	bHasLos = true;
					// }
					//
					// BlackboardComponent->SetValueAsBool(AttackRangeKey.SelectedKeyName,bWithInRange && bHasLos);
					BlackboardComponent->SetValueAsBool(AttackRangeKey.SelectedKeyName,bWithInRange);
				}
			}
		}
		else
		{
			// Target 为空
			BlackboardComponent->SetValueAsBool(AttackRangeKey.SelectedKeyName,false);
		}
	}
}
