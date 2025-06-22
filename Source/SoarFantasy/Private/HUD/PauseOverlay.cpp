// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD/PauseOverlay.h"
#include "Components/Button.h"
#include "Input/KixPlayerController.h"
#include "HUD/SFHUD.h"
#include "HUD/EndOverlay.h"
#include "Characters/Kix/CharactersKix.h"

// ================================
// UPauseOverlay
// ポーズメニューの実装
// Implementation for pause menu overlay
// ================================

// ウィジェット初期化：ボタンにイベントをバインド
// Initialize widget: bind buttons
void UPauseOverlay::NativeConstruct()
{
    if (ResumeButton)
    {
        ResumeButton->OnClicked.AddDynamic(this, &UPauseOverlay::ResumeButtonClicked);
    }
    if (MainMenuButton)
    {
        MainMenuButton->OnClicked.AddDynamic(this, &UPauseOverlay::EndButtonClicked);
    }
}

// 再開ボタン押下時：ポーズを解除してHUD状態をリセット
// Handle Resume button click: unpause game and reset HUD state
void UPauseOverlay::ResumeButtonClicked()
{
    if (GetWorld())
    {
        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        if (PlayerController)
        {
            PlayerController->SetPause(false);
            PlayerController->SetShowMouseCursor(false);
            this->RemoveFromParent();

            // コントローラのポーズ状態を初期化
            AKixPlayerController* KixController = Cast<AKixPlayerController>(PlayerController);
            if (KixController)
            {
                KixController->SetPauseBoolFalse();
            }
        }
    }
}

// メインメニューボタン押下時：エンドメニューを表示してスコアを設定
// Handle Main Menu button click: show end overlay and set scores
void UPauseOverlay::EndButtonClicked()
{
    if (GetWorld())
    {
        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        if (PlayerController)
        {
            ASFHUD* SFHUD = Cast<ASFHUD>(PlayerController->GetHUD());
            if (SFHUD)
            {
                // エンドメニューを表示
                SFHUD->OnOffEndOverlay(true);
                EndOverlay = SFHUD->GetEndOverlay();

                if (EndOverlay)
                {
                    // 現在のスコア情報を設定
                    ACharactersKix* CharacterKix = Cast<ACharactersKix>(PlayerController->GetPawn());
                    EndOverlay->SetBestScore(CharacterKix->GetPlayerCurrentScore());
                    EndOverlay->SetCurrentScore(CharacterKix->GetPlayerCurrentScore());
                    EndOverlay->SetCoinScore(CharacterKix->GetPlayerCoinScoreScore());
                    EndOverlay->SetPerformanceScore(CharacterKix->GetPlayerPerformanceScore());
                    EndOverlay->SetDistancetScore(CharacterKix->GetPlayerDistanceScore());
                }

                // ポーズオーバーレイを閉じる
                this->RemoveFromParent();
            }
        }
    }
}
