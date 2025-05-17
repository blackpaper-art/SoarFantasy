// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MissileSpawnerBASE.generated.h"

UCLASS()
class SOARFANTASY_API AMissileSpawnerBASE : public AActor
{
	GENERATED_BODY()
	
public:	
	AMissileSpawnerBASE();

protected:
	virtual void BeginPlay() override;

	FTimerHandle MissileSpawnTimerHandle;
	FTimerHandle BuffSpawnTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn")
	float MinTimerCount = 3.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn")
	float MaxTimerCount = 15.f;
	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<AActor> BPMissile;
	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<AActor> BPMagnet;

private:
	float RandomTimerCount;
	void SpawnMissile();
	void SpawnBuff();
};
