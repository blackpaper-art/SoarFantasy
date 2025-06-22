// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD/StartOverlay.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/Kix/CharactersKix.h"

// ================================
// UStartOverlay
// ���`���_ʼ����Όgװ
// Implementation for the start screen UI
// ================================

// �ܥ���˥��٥�Ȥ�Х����
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

// �ץ쥤�_ʼ�I��
// Handle Play button click: start game
void UStartOverlay::StartGameButton()
{
    // ���`�Щ`�쥤��Ǳ�ʾ
    // Remove the overlay widget
    RemoveFromParent();

    // �ץ쥤��`����ȥ�`���ȡ�ä������`������_
    // Get player controller and unpause the game
    if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
    {
        PlayerController->SetPause(false);
        PlayerController->SetShowMouseCursor(false);
        PlayerController->SetInputMode(FInputModeGameOnly());
    }

    // �F�ڤΥ�٥�����i���z��
    // Reload current level to start fresh
    UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

// �K�˄I��
// Handle Quit button click: exit game
void UStartOverlay::QuitGameButton()
{
    // ���`�Щ`�쥤��Ǳ�ʾ
    // Remove the overlay widget
    RemoveFromParent();

    // ���`���K��
    // Quit the game
    if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
    {
        UKismetSystemLibrary::QuitGame(this, PlayerController, EQuitPreference::Quit, false);
    }
}
