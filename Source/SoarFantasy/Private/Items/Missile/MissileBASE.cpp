// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Missile/MissileBASE.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/Kix/CharactersKix.h"

AMissileBASE::AMissileBASE()
{
	PrimaryActorTick.bCanEverTick = false;

	MissileSphere = CreateDefaultSubobject<USphereComponent>(TEXT("MissileSphere"));
	RootComponent = MissileSphere;
	

	MissileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MissileMesh"));
	MissileMesh->SetupAttachment(MissileSphere);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
}

void AMissileBASE::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::PlaySound2D(GetWorld(), MissileLaunchedSound);

	MissileSphere->OnComponentBeginOverlap.AddDynamic(this, &AMissileBASE::OnSphereOverlap);
}

void AMissileBASE::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharactersKix* CharacterKix = Cast<ACharactersKix>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (CharacterKix)
	{
		CharacterKix->KixDead();
	}
}

