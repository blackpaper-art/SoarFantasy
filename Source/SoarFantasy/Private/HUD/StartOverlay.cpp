// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD/StartOverlay.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/Kix/CharactersKix.h"

// ================================
// UStartOverlay
// ゲーム開始画面の実装
// Implementation for the start screen UI
// ================================

// ボタンにイベントをバインド
// Bind button click events
void UStartOverlay::NativeConstruct()
{
    if (PlayButton)
    {
        PlayButton->OnClicked.AddDynamic(this, &UStartOverlay::StartGameButton);
    }
    if (QuitButton)
    {
        QuitButton->OnClicked.AddDynamic(this, &UStartOverlay::QuitGameButton);
    }
}

// プレイ開始処理
// Handle Play button click: start game
void UStartOverlay::StartGameButton()
{
    // オーバーレイを非表示
    // Remove the overlay widget
    RemoveFromParent();

    // プレイヤーコントローラを取得し、ゲームを再開
    // Get player controller and unpause the game
    if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
    {
        PlayerController->SetPause(false);
        PlayerController->SetShowMouseCursor(false);
        PlayerController->SetInputMode(FInputModeGameOnly());
    }

    // 現在のレベルを再読み込み
    // Reload current level to start fresh
    UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

// 終了処理
// Handle Quit button click: exit game
void UStartOverlay::QuitGameButton()
{
    // オーバーレイを非表示
    // Remove the overlay widget
    RemoveFromParent();

    // ゲームを終了
    // Quit the game
    if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
    {
        UKismetSystemLibrary::QuitGame(this, PlayerController, EQuitPreference::Quit, false);
    }
}
