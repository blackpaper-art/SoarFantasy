// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Buff/BuffBASE.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Characters/Kix/CharactersKix.h"

ABuffBASE::ABuffBASE()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MissileMesh"));
	RootComponent = StaticMesh;
	StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &ABuffBASE::OverlapBegin);


	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
}

void ABuffBASE::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABuffBASE::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		ACharactersKix* KixCharacter = Cast<ACharactersKix>(OtherActor);
		if (KixCharacter)
		{
			KixCharacter->ActiveKixsMag();
			Destroy();
		}
	}
}

