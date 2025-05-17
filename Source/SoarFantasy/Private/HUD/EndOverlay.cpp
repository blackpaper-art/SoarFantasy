// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/EndOverlay.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "HUD/SFHUD.h"
#include "HUD/StartOverlay.h"

void UEndOverlay::NativeConstruct()
{
	if (MainMenuButton)
	{
		MainMenuButton->OnClicked.AddDynamic(this, &UEndOverlay::PressMainMenuButton);
	}
}

void UEndOverlay::SetBestScore(int32 BestScore)
{
	if (BestScoreText)
	{
		BestScoreText->SetText(FText::FromString(FString::Printf(TEXT("Best Score: %d"), BestScore)));
	}
}

void UEndOverlay::SetCurrentScore(int32 CurrentScore)
{
	if (CurrenScoreText)
	{
		CurrenScoreText->SetText(FText::FromString(FString::Printf(TEXT("%d"), CurrentScore)));
	}
}

void UEndOverlay::SetCoinScore(int32 CointScore)
{
	if (CoinText)
	{
		CoinText->SetText(FText::FromString(FString::Printf(TEXT("Collected Coin: %d"), CointScore)));
	}
}

void UEndOverlay::SetPerformanceScore(int32 PerformanceScore)
{
	if (PerformanceText)
	{
		PerformanceText->SetText(FText::FromString(FString::Printf(TEXT("Performance Score: %d"), PerformanceScore)));
	}
}

void UEndOverlay::SetDistancetScore(int32 DistanceScore)
{
	if (DistanceText)
	{
		DistanceText->SetText(FText::FromString(FString::Printf(TEXT("Distance: %d Metre"), DistanceScore)));
	}
}

void UEndOverlay::PressMainMenuButton()
{
	if (ASFHUD* SFHUD = Cast<ASFHUD>(GetWorld()->GetFirstPlayerController()->GetHUD()))
	{
		this->RemoveFromParent();
		SFHUD->OnOffStartOverlay(true);
	}
}



