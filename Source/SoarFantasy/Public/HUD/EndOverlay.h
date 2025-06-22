// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndOverlay.generated.h"

/**
 * ================================
 * UEndOverlay
 * ゲーム終了画面の UI ウィジェット
 * UI widget for the game end screen
 * ================================
 */
UCLASS()
class SOARFANTASY_API UEndOverlay : public UUserWidget
{
    GENERATED_BODY()

public:
    // スコア表示用の設定関数
    // Functions to set score values

    // ベストスコアを設定
    // Set the best score
    void SetBestScore(int32 BestScore);

    // 現在のスコアを設定
    // Set the current score
    void SetCurrentScore(int32 CurrentScore);

    // コインスコアを設定
    // Set the coin score
    void SetCoinScore(int32 CointScore);

    // パフォーマンススコアを設定
    // Set the performance score
    void SetPerformanceScore(int32 PerformanceScore);

    // 距離スコアを設定
    // Set the distance score
    void SetDistancetScore(int32 DistanceScore);

    // メインメニューへ戻るボタンの処理
    // Function called when the Main Menu button is pressed
    UFUNCTION()
    void PressMainMenuButton();

protected:
    // ウィジェット生成時の初期化処理
    // Called during widget construction
    virtual void NativeConstruct() override;

private:
    // スコア表示用テキスト
    // Text blocks for score display
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

    // メインメニューボタン
    // Button to return to the main menu
    UPROPERTY(meta = (Bindwidget))
    class UButton* MainMenuButton;

    // スタート画面への参照
    // Reference to the start overlay
    class UStartOverlay* StartOverlay;
};
