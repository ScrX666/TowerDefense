// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TManBase.h"

#include "ToolContextInterfaces.h"
#include "AI/TAIBaseController.h"
#include "AI/Enemy/TEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Building/Tower/TMainTower.h"
#include "Character/TSoldierBase.h"
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
#include "Components/SkeletalMeshComponent.h"

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
	AutoPossessAI = EAutoPossessAI::Spawned;
	AIControllerClass = ATAIBaseController::StaticClass();

	HealthWidgetComponent->SetDrawSize(FVector2D(200.0f, 50.0f));

	HealthBarWidget = LoadClass<UUserWidget>(nullptr,TEXT("/Game/UI/U_ManHealth.U_ManHealth_C"));
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	HealthWidgetComponent->SetCollisionProfileName(TEXT("NoCollision"));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Man"));

	// 配置运动组件
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	bUseControllerRotationYaw = false;

	
	// 配置AI感知组件
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	PerceptionComponent->ConfigureSense(*SightConfig);
	PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
	SightConfig->SightRadius = 1000.0f;  // 设置视野范围
	SightConfig->LoseSightRadius = 1200.0f;  // 设置失去目标的视野范围
	SightConfig->PeripheralVisionAngleDegrees = 90.0f;  // 设置感知角度
	SightConfig->SetMaxAge(5.0f);  // 设置感知信息的最大存活时间
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	
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
/*
 * 感知到敌人
 */
void ATManBase::OnPerceptionUpdated(const TArray<AActor*>& Actors)
{
	if( !ManAIC)
		ManAIC = Cast<ATAIBaseController>(GetController());
	if( !ManAIC || !ManAIC->CanBeSoloed()) return ; // 自己在对战的情况下 不设置对战对象
	
	// for( auto SeenActorIt = Actors.end(),SeenActorIt.operator--(); SeenActorIt != Actors.begin(); SeenActorIt.operator--())
	for( int32 i = Actors.Num() - 1; i >= 0; i--)
	{
		const auto SeenActor = Actors[i];
		if( SeenActor->IsA(AttackManCla))
		{
			ATManBase* Man = Cast<ATManBase>(SeenActor);
			ATAIBaseController* TargetAIC = Cast<ATAIBaseController>(Man->GetController());
			if( TargetAIC && Man)
			{
				if( TargetAIC->CanBeSoloed() && ManAIC->CanBeSoloed())
				{
					ManAIC->SetSoloTarget(Man);
					TargetAIC->SetSoloTarget(this);
				}
			}
		}
	}
}

void ATManBase::ManualPerceptionUpdated()
{
	TArray<AActor*> Actors;
	PerceptionComponent->GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(),Actors);
	OnPerceptionUpdated(Actors);
}

void ATManBase::Destroyed()
{
	Super::Destroyed();
	//TODO: 与动画绑定
	if( ManAIC && ManAIC->GetAttackMan())
	ManAIC->GetAttackMan()->ManStateAndBuffer->OnDead.RemoveDynamic(ManAIC,&ATAIBaseController::DisableSolo);
}

// Called when the game starts or when spawned
void ATManBase::BeginPlay()
{
	Super::BeginPlay();
	
	ManAIC = Cast<ATAIBaseController>(Controller); // 运行时生成获取不到Controller
	
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
}

float ATManBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	// DamageCauser->GetOwner() 即获取发射子弹的塔
	if( DamageCauser)
	{
		if( DamageCauser && DamageCauser->IsA<ATMainTower>())
		{
			// 塔的直接伤害
			ManStateAndBuffer->ApplyHealthChange(DamageCauser,-DamageAmount);
		}
		else
		{
			// Buff伤害等
			ManStateAndBuffer->ApplyHealthChange(DamageCauser->GetOwner(),-DamageAmount);
		}
	}
	else
	{
		// 技能
		ManStateAndBuffer->ApplyHealthChange(DamageCauser,-DamageAmount);
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

void ATManBase::Attack()
{
	if( !ManAIC)
		ManAIC = Cast<ATAIBaseController>(GetController());
	
	if(AttackMontage)
		GetMesh()->GetAnimInstance()->Montage_Play(AttackMontage);
	if( ManAIC)
	{
		FVector Direction = ManAIC->GetAttackMan()->GetActorLocation() - this->GetActorLocation();
		Direction.Z = 0;
		FRotator NewRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
		this->SetActorRotation(NewRotation);
	}
}
/*
 * 由动画通知事件触发
 */
void ATManBase::ApplyDamageInAnim()
{
	if( !ManAIC) return ;
	
	AActor* TargetActor = ManAIC->GetAttackMan();
	UGameplayStatics::ApplyDamage(TargetActor,ManStateAndBuffer->ManState.Damage,nullptr,this,UDamageType::StaticClass());
}



void ATManBase::UpdateHealthBarRotation()
{
	const FVector CamLoc = UGameplayStatics::GetPlayerCameraManager(this,0)->GetCameraLocation();
	const FRotator LookAtRoat = FRotationMatrix::MakeFromX(CamLoc - HealthWidgetComponent->GetComponentLocation()).Rotator();
	HealthWidgetComponent->SetWorldRotation(LookAtRoat);
}

