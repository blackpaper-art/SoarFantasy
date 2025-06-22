// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD/SFOverlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

// ====================================
// USFOverlay
// ���`��HUD���`�Щ`�쥤�Όgװ
// Implementation for gameplay HUD overlay
// ====================================

// �������M�åЩ`�Υѩ`����Ʃ`�����O��
// Set coin progress bar percent
void USFOverlay::SetCoinProgressBarPercent(float Percent)
{
    if (CoinProgressBar)
    {
        CoinProgressBar->SetPercent(Percent);
    }
}

// �ѥե��`�ޥ󥹥������ƥ����Ȥ����
// Update performance score text
void USFOverlay::SetPerformanceScore(int32 PerformanceScore)
{
    if (PerformanceText)
    {
        PerformanceText->SetText(FText::FromString(FString::Printf(TEXT("Performance: %d"), PerformanceScore)));
    }
}

// ���x�������ƥ����Ȥ����
// Update distance score text
void USFOverlay::SetDistanceScore(int32 DistanceScore)
{
    if (DistanceText)
    {
        DistanceText->SetText(FText::FromString(FString::Printf(TEXT("Distance: %d"), DistanceScore)));
    }
}
