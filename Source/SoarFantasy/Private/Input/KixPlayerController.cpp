// Fill out your copyright notice in the Description page of Project Settings.

#include "Input/KixPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Characters/Kix/CharactersKix.h"
#include "GameFramework/CharacterMovementComponent.h"

// ================================
// AKixPlayerController
// �ץ쥤��`�����ΥХ�����O��
// Setup input bindings
// ================================
void AKixPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(InputComponent);

    if (EnhancedInputComp)
    {
        // ������
        // Bind Jump
        EnhancedInputComp->BindAction(JumpAction, ETriggerEvent::Started, this, &AKixPlayerController::Jump);
        // ���㤬��
        // Bind Down
        EnhancedInputComp->BindAction(DownAction, ETriggerEvent::Started, this, &AKixPlayerController::Down);
        // ���å���
        // Bind Dash
        EnhancedInputComp->BindAction(DashAction, ETriggerEvent::Started, this, &AKixPlayerController::Dash);
        // �ݩ`��
        // Bind Pause
        EnhancedInputComp->BindAction(PauseAction, ETriggerEvent::Started, this, &AKixPlayerController::PauseGame);
    }
}

// �ݩ`�����Еr�������ޥåԥ󥰤�׷��
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

// �����׌g��
// Execute Jump
void AKixPlayerController::Jump()
{
    CurrentChara->Jump();
}

// �ݩ`����˥�`���Ф��椨
// Toggle Pause Menu
void AKixPlayerController::PauseGame()
{
    if (CurrentPauseUIState == EPauseUIState::SubMenu)
    {
        return;
    }

    if (!bPauseMenuActivating && !CurrentChara->GetOtherOverlayActivating())
    {
        // �ݩ`���_ʼ
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
        // �ݩ`�����
        // End pause
        bPauseMenuActivating = false;
        SetPause(false);
        FInputModeGameOnly InputMode;
        SetInputMode(InputMode);

        CurrentPauseUIState = EPauseUIState::None;
        CurrentChara->OpenOrClosePauseGameMenu(false);
    }
}

// ���㤬���g��
// Execute Down
void AKixPlayerController::Down()
{
    CurrentChara->Down();
}

// ���å���g��
// Execute Dash
void AKixPlayerController::Dash()
{
    CurrentChara->Dash();
}

// �ݩ`��״�B��ꥻ�å�
// Reset pause flags
void AKixPlayerController::SetPauseBoolFalse()
{
    bPauseMenuActivating = false;
    CurrentPauseUIState = EPauseUIState::None;
}
