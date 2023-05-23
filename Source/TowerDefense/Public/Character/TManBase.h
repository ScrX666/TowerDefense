// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TManBase.generated.h"

class ATAIBaseController;
class UAIPerceptionComponent;
class UPawnSensingComponent;
class UWidgetComponent;
class UTManStateAndBuffer;

UCLASS()
class TOWERDEFENSE_API ATManBase : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	FName Name;
	UPROPERTY(VisibleAnywhere)
	UTManStateAndBuffer* ManStateAndBuffer;
	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* HealthWidgetComponent;
	UPROPERTY(VisibleAnywhere)
	TSubclassOf<UUserWidget> HealthBarWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	class UAIPerceptionComponent* PerceptionComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	class UAISenseConfig_Sight* SightConfig;
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* AttackMontage;
	UPROPERTY(VisibleAnywhere)
	TSubclassOf<ATManBase> AttackManCla;
protected:
	UPROPERTY(VisibleAnywhere)
	ATAIBaseController* ManAIC;
public:	
	// Sets default values for this character's properties
	ATManBase();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable,BlueprintPure)
	int GetMaxHealth();
	UFUNCTION(BlueprintCallable,BlueprintPure)
	int GetCurrentHealth();
	UFUNCTION()
	virtual void Attack();
	/*
	 * 由动画通知事件触发
	 */
	UFUNCTION(BlueprintCallable)
	virtual void ApplyDamageInAnim();
	/*
	 * 手动更新感知组件，用于hero更新
	 */
	UFUNCTION()
	void ManualPerceptionUpdated();
	/*
	 * 角色死亡调用
	 */
	UFUNCTION()
	virtual void OnManDead();
	/*
	 * 角色死亡重生
	 */
	UFUNCTION()
	virtual void OnManReborn();
	
protected:
	UFUNCTION()
	void UpdateHealthBar(AActor* InstigatorActor, UTManStateAndBuffer* OwningComp, float NewHealth, float Delta);
	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& Actors);


	virtual void Destroyed() override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:

	/*
	 * 更新UI朝向
	 */
	void UpdateHealthBarRotation();
};
