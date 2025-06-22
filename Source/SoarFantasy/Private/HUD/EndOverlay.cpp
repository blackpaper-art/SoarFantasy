// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD/EndOverlay.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "HUD/SFHUD.h"
#include "HUD/StartOverlay.h"

// ================================
// UEndOverlay
// ゲーム終了画面の処理クラス
// Class handling the game end screen logic
// ================================

// ウィジェット構築時の初期化
// Initialize when widget is constructed
void UEndOverlay::NativeConstruct()
{
    // メインメニューボタンが有効ならクリックイベントをバインド
    // Bind click event if the Main Menu button is valid
    if (MainMenuButton)
    {
        MainMenuButton->OnClicked.AddDynamic(this, &UEndOverlay::PressMainMenuButton);
    }
}

// ベストスコアを設定
// Set the best score text
void UEndOverlay::SetBestScore(int32 BestScore)
{
    if (BestScoreText)
    {
        BestScoreText->SetText(FText::FromString(FString::Printf(TEXT("Best Score: %d"), BestScore)));
    }
}

// 現在のスコアを設定
// Set the current score text
void UEndOverlay::SetCurrentScore(int32 CurrentScore)
{
    if (CurrenScoreText)
    {
        CurrenScoreText->SetText(FText::FromString(FString::Printf(TEXT("%d"), CurrentScore)));
    }
}

// コインスコアを設定
// Set the collected coin score text
void UEndOverlay::SetCoinScore(int32 CointScore)
{
    if (CoinText)
    {
        CoinText->SetText(FText::FromString(FString::Printf(TEXT("Collected Coin: %d"), CointScore)));
    }
}

// パフォーマンススコアを設定
// Set the performance score text
void UEndOverlay::SetPerformanceScore(int32 PerformanceScore)
{
    if (PerformanceText)
    {
        PerformanceText->SetText(FText::FromString(FString::Printf(TEXT("Performance Score: %d"), PerformanceScore)));
    }
}

// 距離スコアを設定
// Set the distance score text
void UEndOverlay::SetDistancetScore(int32 DistanceScore)
{
    if (DistanceText)
    {
        DistanceText->SetText(FText::FromString(FString::Printf(TEXT("Distance: %d Metre"), DistanceScore)));
    }
}

// メインメニューに戻るボタンが押された時の処理
// Handle the event when Main Menu button is pressed
void UEndOverlay::PressMainMenuButton()
{
    // 現在の HUD を取得して、スタート画面を表示
    // Get current HUD and show the start overlay
    if (ASFHUD* SFHUD = Cast<ASFHUD>(GetWorld()->GetFirstPlayerController()->GetHUD()))
    {
        this->RemoveFromParent();
        SFHUD->OnOffStartOverlay(true);
    }
}
