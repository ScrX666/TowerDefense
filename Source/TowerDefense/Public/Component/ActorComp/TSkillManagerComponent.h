// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TSkillManagerComponent.generated.h"


class UTBaseSkill;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UTSkillManagerComponent : public UActorComponent
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere)
	TMap<FName,UTBaseSkill*> SkillsWithName;
	UPROPERTY(VisibleAnywhere)
	TArray<FName> SkillsNameInArray;
	UPROPERTY(EditDefaultsOnly)
	TMap<FName,TSubclassOf<UTBaseSkill>> SkillsCla;
	
public:	
	// Sets default values for this component's properties
	UTSkillManagerComponent();
	UFUNCTION(BlueprintCallable)
	UTBaseSkill* GetSkill(FName SkillName);
	UFUNCTION(BlueprintCallable)
	TArray<FName>& GetAllSkill();
	bool Execute(FName SkillName);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
