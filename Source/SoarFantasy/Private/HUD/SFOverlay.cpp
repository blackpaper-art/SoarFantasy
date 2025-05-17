// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/SFOverlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void USFOverlay::SetCoinProgressBarPercent(float Percent)
{
	if (CoinProgressBar)
	{
		CoinProgressBar->SetPercent(Percent);
	}
}

void USFOverlay::SetPerformanceScore(int32 PerformanceScore)
{
	if (PerformanceText)
	{
		PerformanceText->SetText(FText::FromString(FString::Printf(TEXT("Performance: %d"), PerformanceScore)));
	}
}

void USFOverlay::SetDistanceScore(int32 DistanceScore)
{
	if (DistanceText)
	{
		DistanceText->SetText(FText::FromString(FString::Printf(TEXT("Distance: %d"), DistanceScore)));
	}
}
