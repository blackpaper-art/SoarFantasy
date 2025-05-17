// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SystemItems/SoarFantasyInterface.h"
#include "CoinBASE.generated.h"

UCLASS()
class SOARFANTASY_API ACoinBASE : public AActor, public ISoarFantasyInterface
{
	GENERATED_BODY()
	
public:	
	ACoinBASE();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
	class UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	int32 CoinScore = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	int32 CoinSocreRate = 1;

	//Magnet
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magnet")
	bool bMagnetActive;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magnet")
	FVector MagnetCoinTargetLocation;
	void ActivateMagnet(const FVector& TargetLocation);
	void DeactivateMagnet();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	class USoundBase* CoinCollectionSound;

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	//Magnet
	float MagnetCoinSpeed = 1000.f;
};
