// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TManBase.h"

#include "ToolContextInterfaces.h"
#include "AI/TFirstAIController.h"
#include "Building/Tower/TMainTower.h"
#include "Component/ActorComp/TManStateAndBuffer.h"
#include "Components/CapsuleComponent.h"
#include "Components/ProgressBar.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GamePlay/TDataTableManager.h"
#include "GamePlay/TPlayerController.h"
#include "GamePlay/TPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/PawnSensingComponent.h"

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
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	HealthWidgetComponent->SetCollisionProfileName(TEXT("NoCollision"));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Man"));

	// 配置AI感知组件
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	PerceptionComponent->ConfigureSense(*SightConfig);
	PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
	SightConfig->SightRadius = 1000.0f;  // 设置视野范围
	SightConfig->LoseSightRadius = 1200.0f;  // 设置失去目标的视野范围
	SightConfig->PeripheralVisionAngleDegrees = 90.0f;  // 设置感知角度
	SightConfig->SetMaxAge(5.0f);  // 设置感知信息的最大存活时间
	
	Name = FName(GetClass()->GetFName().ToString());
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

void ATManBase::OnPerceptionUpdated(const TArray<AActor*>& Actors)
{
	
}

// Called when the game starts or when spawned
void ATManBase::BeginPlay()
{
	Super::BeginPlay();
	
	HealthWidgetComponent->SetWidget(CreateWidget(GetWorld(),HealthBarWidget));
	
	// 绑定事件
	ManStateAndBuffer->OnHealthChanged.AddDynamic(this, &ATManBase::UpdateHealthBar);
	
	PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &ATManBase::OnPerceptionUpdated);
}

// Called every frame
void ATManBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateHealthBarRotation();

}

void ATManBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if( !IsValid(ManStateAndBuffer)) return ;
	// 根据Name加载信息
	ManStateAndBuffer->ManState = TDataTableManager::GetInstance()->GetManStateData(Name);
	ManStateAndBuffer->CurrentHealth = ManStateAndBuffer->ManState.MaxHealth;
	GetMesh()->SetSkeletalMesh(ManStateAndBuffer->ManState.SkeletalMesh);
}

float ATManBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	// DamageCauser->GetOwner() 即获取发射子弹的塔
	if( DamageCauser->IsA<ATMainTower>())
	{
		ManStateAndBuffer->ApplyHealthChange(DamageCauser,-DamageAmount);
	}
	else
	{
		ManStateAndBuffer->ApplyHealthChange(DamageCauser->GetOwner(),-DamageAmount);
	}

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

