// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/CoinBASE.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Characters/Kix/CharactersKix.h"

ACoinBASE::ACoinBASE()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMeshComp;
	StaticMeshComp->OnComponentBeginOverlap.AddDynamic(this, &ACoinBASE::OverlapBegin);
}




void ACoinBASE::BeginPlay()
{
	Super::BeginPlay();

	CoinScore = CoinSocreRate * CoinScore;
}

void ACoinBASE::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bMagnetActive)
	{
		FVector NewLocation = FMath::VInterpConstantTo(GetActorLocation(), MagnetCoinTargetLocation, DeltaTime, MagnetCoinSpeed);
		SetActorLocation(NewLocation);
	}
}

void ACoinBASE::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (OtherActor && OtherActor != this)
	{
		ACharactersKix* KixCharacter = Cast<ACharactersKix>(OtherActor);
		if (KixCharacter)
		{
			KixCharacter->AddCoinScore(CoinScore);
			UGameplayStatics::PlaySound2D(GetWorld(), CoinCollectionSound);
			Destroy();
		}
	}
}

void ACoinBASE::ActivateMagnet(const FVector& TargetLocation)
{

	bMagnetActive = true;
	MagnetCoinTargetLocation = TargetLocation;
}

void ACoinBASE::DeactivateMagnet()
{
	bMagnetActive = false;
}
