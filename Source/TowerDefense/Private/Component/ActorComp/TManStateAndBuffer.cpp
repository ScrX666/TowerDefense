// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ActorComp/TManStateAndBuffer.h"

#include "Building/Tower/TMainTower.h"
#include "GamePlay/TPlayerController.h"
#include "GamePlay/TPlayerState.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTManStateAndBuffer::UTManStateAndBuffer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTManStateAndBuffer::DestorySelf(AActor* InstigatorActor)
{
	GetOwner()->Destroy();
}

// Called when the game starts
void UTManStateAndBuffer::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	// 注意顺序 被销毁后不再执行
	OnDead.AddDynamic(this,&UTManStateAndBuffer::AddCoinsAndExp);
	OnDead.AddDynamic(this,&UTManStateAndBuffer::DestorySelf);
}


// Called every frame
void UTManStateAndBuffer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTManStateAndBuffer::ApplyHealthChange(AActor* Instigator,float Delta)
{
	CurrentHealth += Delta;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, ManState.MaxHealth);
	OnHealthChanged.Broadcast(Instigator,this, CurrentHealth,Delta);
	//TODO: 添加死亡事件
	if( CurrentHealth == 0)
		OnDead.Broadcast(Instigator);
}

void UTManStateAndBuffer::AddCoinsAndExp(AActor* InstigatorActor)
{
	UE_LOG(LogTemp,Log,TEXT("Destory Man AddCoins"));
	auto TPlayerControl = Cast<ATPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	// Get Coins
	if( TPlayerControl)
	{
		TPlayerControl->TPlayerState->AddCoins(ManState.Coins);
	}

	// Get Exp
	if( InstigatorActor && InstigatorActor->IsA<ATMainTower>())
	{
		Cast<ATMainTower>(InstigatorActor)->GetExp(ManState.Exp);
	}
}
