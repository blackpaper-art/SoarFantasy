// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD/SFOverlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

// ====================================
// USFOverlay
// ゲームHUDオーバーレイの実装
// Implementation for gameplay HUD overlay
// ====================================

// コイン進捗バーのパーセンテージを設定
// Set coin progress bar percent
void USFOverlay::SetCoinProgressBarPercent(float Percent)
{
    if (CoinProgressBar)
    {
        CoinProgressBar->SetPercent(Percent);
    }
}

// パフォーマンススコアテキストを更新
// Update performance score text
void USFOverlay::SetPerformanceScore(int32 PerformanceScore)
{
    if (PerformanceText)
    {
        PerformanceText->SetText(FText::FromString(FString::Printf(TEXT("Performance: %d"), PerformanceScore)));
    }
}

// 距離スコアテキストを更新
// Update distance score text
void USFOverlay::SetDistanceScore(int32 DistanceScore)
{
    if (DistanceText)
    {
        DistanceText->SetText(FText::FromString(FString::Printf(TEXT("Distance: %d"), DistanceScore)));
    }
}
