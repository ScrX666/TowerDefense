// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "Structure/FAISpawnStruct.h"
#include "TSplineMapActor.generated.h"

UCLASS()
class TOWERDEFENSE_API ATSplineMapActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATSplineMapActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void AddArrow();
	UFUNCTION()
	void AIMove(ATFirstAIController* NPC);
	UFUNCTION()
	void SpawnAI();
	void SpawnWave();
	
protected:
	UPROPERTY(VisibleAnywhere)
	USplineComponent* SplineComponent;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> BP_AICharacter;
	FVector FirstMoveLoc;

	FAISpawnStruct FaiSpawnStruct;
public:
	UFUNCTION()
	void MoveTo(ATFirstAIController* AIController, int index, FVector& NextPosition);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	int32 WaveEnemyCount = 3; // 每波敌人数量

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	int32 TotalWaveCount = 2; // 总波次数量

	protected:
	int32 CurrentWave = 0; // 当前波次
	int32 CurrentEnemyCount = 0; // 当前波次已经生成的敌人数量
	FTimerHandle WaveTimerHandle;
};
