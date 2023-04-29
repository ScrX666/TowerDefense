// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TManBase.h"

#include "ToolContextInterfaces.h"
#include "AI/TFirstAIController.h"
#include "Component/ActorComp/TManStateAndBuffer.h"
#include "Components/ProgressBar.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GamePlay/TDataTableManager.h"
#include "GamePlay/TPlayerController.h"
#include "GamePlay/TPlayerState.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATManBase::ATManBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ManStateAndBuffer = CreateDefaultSubobject<UTManStateAndBuffer>(TEXT("ManStateAndBuffer"));
	GetCharacterMovement()->bOrientRotationToMovement = true;
	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthWidgetComp"));
	HealthWidgetComponent->SetupAttachment(RootComponent);
	HealthWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));
	//AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ATFirstAIController::StaticClass();

	HealthWidgetComponent->SetDrawSize(FVector2D(200.0f, 50.0f));

	HealthBarWidget = LoadClass<UUserWidget>(nullptr,TEXT("/Game/UI/U_ManHealth.U_ManHealth_C"));
	
}

void ATManBase::UpdateHealthBar(AActor* InstigatorActor, UTManStateAndBuffer* OwningComp, float NewHealth, float Delta)
{
	UUserWidget* InfoWidget = HealthWidgetComponent->GetUserWidgetObject();
	if (InfoWidget) {
		auto ProgressBar = Cast<UProgressBar>(InfoWidget->GetWidgetFromName(TEXT("PB_Health")));
		if (ProgressBar)
			ProgressBar->SetPercent(NewHealth / GetMaxHealth());
		else
		{
			UE_LOG(LogTemp,Warning,TEXT("Progress NULL"));
		}
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Info Widge NULL"));
	}
}

void ATManBase::DestorySelf()
{
	UE_LOG(LogTemp,Log,TEXT("Destory Man"));
	this->Destroy();
}

void ATManBase::AddCoins()
{
	UE_LOG(LogTemp,Log,TEXT("Destory Man AddCoins"));
	auto TPlayerControl = Cast<ATPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if( TPlayerControl)
	{
		TPlayerControl->TPlayerState->AddCoins(ManStateAndBuffer->ManState.Coins);
	}
}

// Called when the game starts or when spawned
void ATManBase::BeginPlay()
{
	Super::BeginPlay();
	
	HealthWidgetComponent->SetWidget(CreateWidget(GetWorld(),HealthBarWidget));
	
	// 绑定事件
	ManStateAndBuffer->OnHealthChanged.AddDynamic(this, &ATManBase::UpdateHealthBar);

	// 注意顺序 被销毁后不再执行
	ManStateAndBuffer->OnDead.AddDynamic(this,&ATManBase::AddCoins);
	ManStateAndBuffer->OnDead.AddDynamic(this,&ATManBase::DestorySelf);
}

// Called every frame
void ATManBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateHealthBarRotation();

}

// Called to bind functionality to input
void ATManBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATManBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	// 根据Name加载信息
	ManStateAndBuffer->ManState = TDataTableManager::GetInstance()->GetManStateData(Name);
	ManStateAndBuffer->CurrentHealth = ManStateAndBuffer->ManState.MaxHealth;
	GetMesh()->SetSkeletalMesh(ManStateAndBuffer->ManState.SkeletalMesh);
}

float ATManBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	ManStateAndBuffer->ApplyHealthChange(DamageCauser,-DamageAmount);

	return DamageAmount;
}

int ATManBase::GetMaxHealth()
{
	return ManStateAndBuffer->ManState.MaxHealth;
}

int ATManBase::GetCurrentHealth()
{
	return ManStateAndBuffer->CurrentHealth;
}

void ATManBase::UpdateHealthBarRotation()
{
	const FVector CamLoc = UGameplayStatics::GetPlayerCameraManager(this,0)->GetCameraLocation();
	const FRotator LookAtRoat = FRotationMatrix::MakeFromX(CamLoc - HealthWidgetComponent->GetComponentLocation()).Rotator();
	HealthWidgetComponent->SetWorldRotation(LookAtRoat);
}

