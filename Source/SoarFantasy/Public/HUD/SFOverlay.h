// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SFOverlay.generated.h"

/**
 * ====================================
 * USFOverlay
 * ���`��ץ쥤�Ф�UI���`�Щ`�쥤
 * Gameplay HUD overlay widget
 * ====================================
 */
UCLASS()
class SOARFANTASY_API USFOverlay : public UUserWidget
{
    GENERATED_BODY()

public:
    // �������M�åЩ`�θ���
    // Set the percent value for the coin progress bar
    void SetCoinProgressBarPercent(float Percent);

    // �ѥե��`�ޥ󥹥������α�ʾ����
    // Set performance score text
    void SetPerformanceScore(int32 PerformanceScore);

    // ���x�������α�ʾ����
    // Set distance score text
    void SetDistanceScore(int32 DistanceScore);

private:
    // �������M�åЩ`
    // Progress bar for collected coins
    UPROPERTY(meta = (BindWidget))
    class UProgressBar* CoinProgressBar;

    // �ѥե��`�ޥ󥹥������ƥ�����
    // Text block for performance score
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* PerformanceText;

    // ���x�������ƥ�����
    // Text block for distance score
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* DistanceText;
};
