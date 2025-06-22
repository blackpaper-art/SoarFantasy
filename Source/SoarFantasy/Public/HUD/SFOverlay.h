// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SFOverlay.generated.h"

/**
 * ====================================
 * USFOverlay
 * ゲームプレイ中のUIオーバーレイ
 * Gameplay HUD overlay widget
 * ====================================
 */
UCLASS()
class SOARFANTASY_API USFOverlay : public UUserWidget
{
    GENERATED_BODY()

public:
    // コイン進捗バーの更新
    // Set the percent value for the coin progress bar
    void SetCoinProgressBarPercent(float Percent);

    // パフォーマンススコアの表示更新
    // Set performance score text
    void SetPerformanceScore(int32 PerformanceScore);

    // 距離スコアの表示更新
    // Set distance score text
    void SetDistanceScore(int32 DistanceScore);

private:
    // コイン進捗バー
    // Progress bar for collected coins
    UPROPERTY(meta = (BindWidget))
    class UProgressBar* CoinProgressBar;

    // パフォーマンススコアテキスト
    // Text block for performance score
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* PerformanceText;

    // 距離スコアテキスト
    // Text block for distance score
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* DistanceText;
};
