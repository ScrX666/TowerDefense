// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structure/FTManBuffer.h"
#include "Structure/FTManState.h"
#include "Enum/EManBufferType.h"
#include "TManStateAndBuffer.generated.h"


class UNiagaraComponent;
class ATManBase;
class UCharacterMovementComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, UTManStateAndBuffer*,
                                              OwningComp, float, NewHealth, float, Delta);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDead, AActor*, InstigatorActor);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UTManStateAndBuffer : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this component's properties
	// 状态
	UPROPERTY(VisibleAnywhere)
	FTManState ManState;
	UPROPERTY(VisibleAnywhere)
	float CurrentHealth;
	UPROPERTY(BlueprintAssignable,BlueprintReadOnly)
	FOnHealthChanged OnHealthChanged;
	UPROPERTY(BlueprintAssignable,BlueprintReadOnly)
	FOnDead OnDead;

	// Buffer 增益
	// TODO: 添加Buffer
	// UPROPERTY(VisibleAnywhere)
	// TArray<FTManBuffer> Buffers;d
	
protected:
	UFUNCTION()
	void DestorySelf(AActor* InstigatorActor);
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	// BUFF
	TMap<EManBufferType,FTimerHandle> BufferTimerHandles;
	UPROPERTY()
	TMap<EManBufferType,AActor*> BufferInstigators;
	UPROPERTY()
	TMap<EManBufferType,UNiagaraComponent*> BufferNiagaraSystems;

	UPROPERTY(VisibleAnywhere)
	ATManBase* Owner;
	UPROPERTY(VisibleAnywhere)
	UCharacterMovementComponent* CharacterMovementComp;

	float OrignWalkSpeed;
	float PoisonDamage;
	
public:	
	UTManStateAndBuffer();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 状态
	void ApplyHealthChange(AActor* Instigator, float Delta);

	UFUNCTION()
	void AddCoinsAndExp(AActor* InstigatorActor);

	// Buffer 增益
	/*
	 * 激活Buffer
	 */
	void ActivateBuffer(const TArray<FTManBuffer> &Buffers,AActor* Instigator);

private:
	/*
	 * 施加减速
	 */
	void ActiveIce(const FTManBuffer& Buffer);
	/*
	 * 施加持续伤害
	 */
	void ActivePoison(const FTManBuffer& Buffer);

	UFUNCTION()
	void DeActiveIce();
	UFUNCTION()
	void DeActivePoison();

	UFUNCTION()
	void ApplyPoisonDamage();

	void ActiveBufferEffect(const FTManBuffer& Buffer, FName SocketName);
	void DeActiveBufferEffect(const EManBufferType ManBufferType);
};
