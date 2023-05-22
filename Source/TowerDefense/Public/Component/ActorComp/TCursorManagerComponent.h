// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TCursorManagerComponent.generated.h"

/*
 * 没有用, UE中已提供了相应的逻辑
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UTCursorManagerComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	TMap<TEnumAsByte<EMouseCursor::Type>,TSubclassOf<UUserWidget>> CursorWidgetCla;
	UPROPERTY(VisibleAnywhere)
	TMap<TEnumAsByte<EMouseCursor::Type>,UUserWidget*> CursorWidgets;
	
public:	
	// Sets default values for this component's properties
	UTCursorManagerComponent();
	/*
	 * 设置Cursor
	 */
	void SetCursorType(APlayerController* PC, EMouseCursor::Type CursorType);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
