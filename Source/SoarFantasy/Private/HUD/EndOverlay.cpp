// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD/EndOverlay.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "HUD/SFHUD.h"
#include "HUD/StartOverlay.h"

// ================================
// UEndOverlay
// ���`��K�˻���΄I���饹
// Class handling the game end screen logic
// ================================

// ���������åȘ��B�r�γ��ڻ�
// Initialize when widget is constructed
void UEndOverlay::NativeConstruct()
{
    // �ᥤ���˥�`�ܥ����Є��ʤ饯��å����٥�Ȥ�Х����
    // Bind click event if the Main Menu button is valid
    if (MainMenuButton)
    {
        MainMenuButton->OnClicked.AddDynamic(this, &UEndOverlay::PressMainMenuButton);
    }
}

// �٥��ȥ��������O��
// Set the best score text
void UEndOverlay::SetBestScore(int32 BestScore)
{
    if (BestScoreText)
    {
        BestScoreText->SetText(FText::FromString(FString::Printf(TEXT("Best Score: %d"), BestScore)));
    }
}

// �F�ڤΥ��������O��
// Set the current score text
void UEndOverlay::SetCurrentScore(int32 CurrentScore)
{
    if (CurrenScoreText)
    {
        CurrenScoreText->SetText(FText::FromString(FString::Printf(TEXT("%d"), CurrentScore)));
    }
}

// �����󥹥������O��
// Set the collected coin score text
void UEndOverlay::SetCoinScore(int32 CointScore)
{
    if (CoinText)
    {
        CoinText->SetText(FText::FromString(FString::Printf(TEXT("Collected Coin: %d"), CointScore)));
    }
}

// �ѥե��`�ޥ󥹥��������O��
// Set the performance score text
void UEndOverlay::SetPerformanceScore(int32 PerformanceScore)
{
    if (PerformanceText)
    {
        PerformanceText->SetText(FText::FromString(FString::Printf(TEXT("Performance Score: %d"), PerformanceScore)));
    }
}

// ���x���������O��
// Set the distance score text
void UEndOverlay::SetDistancetScore(int32 DistanceScore)
{
    if (DistanceText)
    {
        DistanceText->SetText(FText::FromString(FString::Printf(TEXT("Distance: %d Metre"), DistanceScore)));
    }
}

// �ᥤ���˥�`�ˑ���ܥ���Ѻ���줿�r�΄I��
// Handle the event when Main Menu button is pressed
void UEndOverlay::PressMainMenuButton()
{
    // �F�ڤ� HUD ��ȡ�ä��ơ������`�Ȼ�����ʾ
    // Get current HUD and show the start overlay
    if (ASFHUD* SFHUD = Cast<ASFHUD>(GetWorld()->GetFirstPlayerController()->GetHUD()))
    {
        this->RemoveFromParent();
        SFHUD->OnOffStartOverlay(true);
    }
}
