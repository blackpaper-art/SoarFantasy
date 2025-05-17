// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GroundBASE.generated.h"

UCLASS()
class SOARFANTASY_API AGroundBASE : public AActor
{
	GENERATED_BODY()
	
public:	
	AGroundBASE();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
	class UStaticMeshComponent* StaticMeshComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	class UBoxComponent* BoxCollisionComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float PlatformMoveSpeedRate = 1.f;

	//GroundPosition
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location", meta = (ExposeOnSpawn = "true"))
	float GroundPostionY;
	FVector SpawnLocation;
	FVector GroundLocation;

	//Binded with Coin
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
	TSubclassOf<AActor> CoinClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin", meta = (ExposeOnSpawn = "true"))
	int32 CoinCount = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
	float CoinSpacing = 40.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
	TArray<UChildActorComponent*> CoinComponents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style")
	int32 PlatformStyle = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
	int32 CoinStyle = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle")
	int32 ObstacleStyle = 0;

	//EnemyLayer
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	TSubclassOf<AActor> EnemySphereClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	TSubclassOf<AActor> EnemyConeClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy", meta = (ExposeOnSpawn = "true"))
	int32 EnemyTypeNum = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	TArray<UChildActorComponent*> EnemyComponents;

protected:
	virtual void BeginPlay() override;

private:

	float PlatformMoveSpeedBase = -600.f;
	float PlatformCurrentSpeed;
};
