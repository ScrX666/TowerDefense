// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/TBuildingInterface.h"
#include "TMainBuilding.generated.h"

UCLASS()
class TOWERDEFENSE_API ATMainBuilding : public AActor, public ITBuildingInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATMainBuilding();

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* BuildingMesh;
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	UPROPERTY(EditAnywhere)
	TMap<FName, UMaterialInterface*> Materials;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruct(ATMainAttachBase* AttachBase) override;
	UFUNCTION(BlueprintCallable)
	virtual void OnDestory() override;
	virtual void OnHovered(bool bHovered) override;
	virtual void OnSelected(bool bSelected);
	virtual int32 GetCostCoins();
	/*
	 * 根据状态改变材质
	 */
	UFUNCTION(BlueprintCallable)
	void CanConstructBuilding(bool bCanConstructBuild);

private:

	void ChangeMaterial(FName Name);
};
