// Fill out your copyright notice in the Description page of Project Settings.


#include "Building/TMainBuilding.h"

#include "GamePlay/TPlayerController.h"
#include "GamePlay/TPlayerState.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATMainBuilding::ATMainBuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
	BuildingMesh->SetCollisionProfileName(TEXT("Building"));
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	BuildingMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATMainBuilding::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATMainBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATMainBuilding::OnConstruct(ATMainAttachBase* AttachBase)
{
}

void ATMainBuilding::OnDestory()
{
	ATPlayerController* PC = Cast<ATPlayerController>(UGameplayStatics::GetPlayerController(this,0));
	if( PC)
	{
		PC->TPlayerState->AddCoins(GetCostCoins() * 0.6f);
	}
	this->Destroy();
	UE_LOG(LogTemp,Log,TEXT("Building Destory"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Building Destory"));
}

void ATMainBuilding::OnHovered(bool bHovered)
{
	UE_LOG(LogTemp, Log, TEXT("Hover"));
	// int i = 0;
	// if( bHovered)
	// {
	// 	i = 1;
	// }
	// else
	// 	i = 2;
	// UE_LOG(LogTemp, Log,TEXT("%d"), i);
	
}

void ATMainBuilding::OnSelected(bool bSelected)
{
}

int32 ATMainBuilding::GetCostCoins()
{
	return 100;
}

void ATMainBuilding::CanConstructBuilding(bool bCanConstructBuild)
{
	if( bCanConstructBuild)
	{
		ChangeMaterial(TEXT("Green"));
	}
	else
	{
		ChangeMaterial(TEXT("Red"));
	}
}

void ATMainBuilding::ChangeMaterial(FName Name)
{
	if( Materials.Num() == 0)
	{
		UE_LOG(LogTemp,Warning,TEXT("Materials None"));
		return ;
	}
	
	UMaterialInterface* Material = *Materials.Find(Name);
	if( Material != nullptr)
	{
		TArray<USceneComponent*> OutChildren;
		RootComponent->GetChildrenComponents(true, OutChildren);
		if( RootComponent != nullptr) OutChildren.Add(RootComponent);
		for( const auto Comp : OutChildren)
		{
			if( Comp->IsA<UMeshComponent>())
			{
				UMeshComponent* Mesh = Cast<UMeshComponent>(Comp);
				const int MaterialCount = Mesh->GetMaterials().Num();
				for( int i = 0; i < MaterialCount; ++i)
				{
					Mesh->SetMaterial(i, Material);
				}
			}
		}
	}
}

