// Fill out your copyright notice in the Description page of Project Settings.

#include "Input/KixPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Characters/Kix/CharactersKix.h"
#include "GameFramework/CharacterMovementComponent.h"

// ================================
// AKixPlayerController
// プレイヤー入力のバインド設定
// Setup input bindings
// ================================
void AKixPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(InputComponent);

    if (EnhancedInputComp)
    {
        // ジャンプ
        // Bind Jump
        EnhancedInputComp->BindAction(JumpAction, ETriggerEvent::Started, this, &AKixPlayerController::Jump);
        // しゃがむ
        // Bind Down
        EnhancedInputComp->BindAction(DownAction, ETriggerEvent::Started, this, &AKixPlayerController::Down);
        // ダッシュ
        // Bind Dash
        EnhancedInputComp->BindAction(DashAction, ETriggerEvent::Started, this, &AKixPlayerController::Dash);
        // ポーズ
        // Bind Pause
        EnhancedInputComp->BindAction(PauseAction, ETriggerEvent::Started, this, &AKixPlayerController::PauseGame);
    }
}

// ポーン所有時に入力マッピングを追加
// Add input mapping context when possessing pawn
void AKixPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    CurrentChara = Cast<ACharactersKix>(InPawn);

    if (ULocalPlayer* LP = GetLocalPlayer())
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            Subsystem->AddMappingContext(CurrentMappingContext, 0);
        }
    }
}

// ジャンプ実行
// Execute Jump
void AKixPlayerController::Jump()
{
    CurrentChara->Jump();
}

// ポーズメニューの切り替え
// Toggle Pause Menu
void AKixPlayerController::PauseGame()
{
    if (CurrentPauseUIState == EPauseUIState::SubMenu)
    {
        return;
    }

    if (!bPauseMenuActivating && !CurrentChara->GetOtherOverlayActivating())
    {
        // ポーズ開始
        // Start pause
        SetPause(true);
        bPauseMenuActivating = true;
        FInputModeUIOnly InputMode;
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
        SetInputMode(InputMode);

        CurrentPauseUIState = EPauseUIState::MainMenu;
        CurrentChara->OpenOrClosePauseGameMenu(true);
    }
    else if (bPauseMenuActivating && CurrentPauseUIState == EPauseUIState::MainMenu)
    {
        // ポーズ解除
        // End pause
        bPauseMenuActivating = false;
        SetPause(false);
        FInputModeGameOnly InputMode;
        SetInputMode(InputMode);

        CurrentPauseUIState = EPauseUIState::None;
        CurrentChara->OpenOrClosePauseGameMenu(false);
    }
}

// しゃがむ実行
// Execute Down
void AKixPlayerController::Down()
{
    CurrentChara->Down();
}

// ダッシュ実行
// Execute Dash
void AKixPlayerController::Dash()
{
    CurrentChara->Dash();
}

// ポーズ状態をリセット
// Reset pause flags
void AKixPlayerController::SetPauseBoolFalse()
{
    bPauseMenuActivating = false;
    CurrentPauseUIState = EPauseUIState::None;
}
