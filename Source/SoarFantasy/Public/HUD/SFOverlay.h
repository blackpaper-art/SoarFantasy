// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SFOverlay.generated.h"

/**
 * 
 */
UCLASS()
class SOARFANTASY_API USFOverlay : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetCoinProgressBarPercent(float Percent);
	void SetPerformanceScore(int32 PerformanceScore);
	void SetDistanceScore(int32 DistanceScore);

private:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* CoinProgressBar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PerformanceText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DistanceText;

};
