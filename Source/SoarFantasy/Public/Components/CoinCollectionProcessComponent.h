// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CoinCollectionProcessComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOARFANTASY_API UCoinCollectionProcessComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCoinCollectionProcessComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;		

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Coin Percent")
	float CurrentCoinPercent;
	UPROPERTY(EditAnywhere, Category = "Coin Percent")
	float MaxCoinPercent;
};
