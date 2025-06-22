// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD/PauseOverlay.h"
#include "Components/Button.h"
#include "Input/KixPlayerController.h"
#include "HUD/SFHUD.h"
#include "HUD/EndOverlay.h"
#include "Characters/Kix/CharactersKix.h"

// ================================
// UPauseOverlay
// �ݩ`����˥�`�Όgװ
// Implementation for pause menu overlay
// ================================

// ���������åȳ��ڻ����ܥ���˥��٥�Ȥ�Х����
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

// ���_�ܥ���Ѻ�r���ݩ`����������HUD״�B��ꥻ�å�
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

            // ����ȥ�`��Υݩ`��״�B����ڻ�
            AKixPlayerController* KixController = Cast<AKixPlayerController>(PlayerController);
            if (KixController)
            {
                KixController->SetPauseBoolFalse();
            }
        }
    }
}

// �ᥤ���˥�`�ܥ���Ѻ�r������ɥ�˥�`���ʾ���ƥ��������O��
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
                // ����ɥ�˥�`���ʾ
                SFHUD->OnOffEndOverlay(true);
                EndOverlay = SFHUD->GetEndOverlay();

                if (EndOverlay)
                {
                    // �F�ڤΥ����������O��
                    ACharactersKix* CharacterKix = Cast<ACharactersKix>(PlayerController->GetPawn());
                    EndOverlay->SetBestScore(CharacterKix->GetPlayerCurrentScore());
                    EndOverlay->SetCurrentScore(CharacterKix->GetPlayerCurrentScore());
                    EndOverlay->SetCoinScore(CharacterKix->GetPlayerCoinScoreScore());
                    EndOverlay->SetPerformanceScore(CharacterKix->GetPlayerPerformanceScore());
                    EndOverlay->SetDistancetScore(CharacterKix->GetPlayerDistanceScore());
                }

                // �ݩ`�����`�Щ`�쥤���]����
                this->RemoveFromParent();
            }
        }
    }
}
