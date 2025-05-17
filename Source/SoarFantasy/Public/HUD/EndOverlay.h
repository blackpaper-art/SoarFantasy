// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndOverlay.generated.h"

/**
 * 
 */
UCLASS()
class SOARFANTASY_API UEndOverlay : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//Score
	void SetBestScore(int32 BestScore);
	void SetCurrentScore(int32 CurrentScore);
	void SetCoinScore(int32 CointScore);
	void SetPerformanceScore(int32 PerformanceScore);
	void SetDistancetScore(int32 DistanceScore);

	//Button
	UFUNCTION()
	void PressMainMenuButton();

protected:
	virtual void NativeConstruct() override;

private:
	//Text
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* BestScoreText;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CurrenScoreText;	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CoinText;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PerformanceText;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DistanceText;

	//Button
	UPROPERTY(meta = (Bindwidget))
	class UButton* MainMenuButton;

	//Overlay
	class UStartOverlay* StartOverlay;
};
