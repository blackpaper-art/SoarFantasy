// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Spawners/MissileSpawnerBASE.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"

AMissileSpawnerBASE::AMissileSpawnerBASE()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AMissileSpawnerBASE::BeginPlay()
{
	Super::BeginPlay();
	
	RandomTimerCount = FMath::RandRange(MinTimerCount, MaxTimerCount);
	GetWorldTimerManager().SetTimer(MissileSpawnTimerHandle, this, &AMissileSpawnerBASE::SpawnMissile, RandomTimerCount, true);
	GetWorldTimerManager().SetTimer(BuffSpawnTimerHandle, this, &AMissileSpawnerBASE::SpawnBuff, 30, true);
}

void AMissileSpawnerBASE::SpawnMissile()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!PlayerPawn)
	{
		return;
	}

	FVector MyLocation = GetActorLocation();
	
	float PlayerZ = PlayerPawn->GetActorLocation().Z + 200.f;

	FRotator PlayerRotator = FRotator(0, 180, 0);

	FVector SpawnLoaction = FVector(MyLocation.X, MyLocation.Y, PlayerZ);
	GetWorld()->SpawnActor<AActor>(BPMissile, SpawnLoaction, PlayerRotator);
}

void AMissileSpawnerBASE::SpawnBuff()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!PlayerPawn)
	{
		return;
	}

	FVector MyLocation = GetActorLocation();
	float PlayerZ = PlayerPawn->GetActorLocation().Z;

	FRotator PlayerRotator = FRotator(0, 180, 0);

	FVector SpawnLoaction = FVector(MyLocation.X, MyLocation.Y, PlayerZ);
	GetWorld()->SpawnActor<AActor>(BPMagnet, SpawnLoaction, PlayerRotator);
}
