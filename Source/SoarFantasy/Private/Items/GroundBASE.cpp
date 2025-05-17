// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/GroundBASE.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ChildActorComponent.h"
#include "Items/CoinBASE.h"

AGroundBASE::AGroundBASE()
{
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	BoxCollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));

	RootComponent = BoxCollisionComp;
	StaticMeshComp->SetupAttachment(BoxCollisionComp);	
}

void AGroundBASE::BeginPlay()
{
	Super::BeginPlay();
	
	PlatformCurrentSpeed = PlatformMoveSpeedBase * PlatformMoveSpeedRate;
	if (CoinClass)
	{
		const float TotalWidth = CoinCount * CoinSpacing;
		const float StartY = -TotalWidth / 2 + CoinSpacing / 2;

		for (int32 i = 0; i < CoinCount; ++i)
		{
			FString Name = FString::Printf(TEXT("CoinChildComp_%d"), i);
			UChildActorComponent* CoinComp = NewObject<UChildActorComponent>(this, FName(*Name));
			if (CoinComp)
			{
				CoinComp->SetupAttachment(RootComponent);
				CoinComp->RegisterComponent();
				CoinComp->SetChildActorClass(CoinClass);
				if (EnemyTypeNum > 0)
				{
					CoinComp->SetRelativeLocation(FVector(StartY + i * CoinSpacing + 20.f, 0.f, 400.f));
				}
				else {
					CoinComp->SetRelativeLocation(FVector(StartY + i * CoinSpacing + 20.f, 0.f, 300.f));
				}
				CoinComponents.Add(CoinComp);
			}
		}
	}

	if (EnemyTypeNum > 0)
	{
		FString Name = FString::Printf(TEXT("EnemyComponent_%d"), EnemyTypeNum);
		UChildActorComponent* EnemyComp = NewObject<UChildActorComponent>(this, FName(*Name));
		if (EnemyComp)
		{
			EnemyComp->SetupAttachment(RootComponent);
			EnemyComp->RegisterComponent();

			switch (EnemyTypeNum)
			{
			case 1:
				if (EnemySphereClass)
					EnemyComp->SetChildActorClass(EnemySphereClass);
					EnemyComp->SetRelativeLocation(FVector(110.f, 0.f, 150.f));
				break;
			case 2:
				if (EnemyConeClass)
					EnemyComp->SetChildActorClass(EnemyConeClass);
					EnemyComp->SetRelativeLocation(FVector(110.f, 0.f, 200.f));
				break;
			default:
				break;
			}

			EnemyComponents.Add(EnemyComp);
		}
	}
}

void AGroundBASE::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalOffset(FVector(PlatformCurrentSpeed * DeltaTime, 0.f, 0.f));
}

