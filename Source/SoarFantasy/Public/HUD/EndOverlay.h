// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndOverlay.generated.h"

/**
 * ================================
 * UEndOverlay
 * ���`��K�˻���� UI ���������å�
 * UI widget for the game end screen
 * ================================
 */
UCLASS()
class SOARFANTASY_API UEndOverlay : public UUserWidget
{
    GENERATED_BODY()

public:
    // ��������ʾ�ä��O���v��
    // Functions to set score values

    // �٥��ȥ��������O��
    // Set the best score
    void SetBestScore(int32 BestScore);

    // �F�ڤΥ��������O��
    // Set the current score
    void SetCurrentScore(int32 CurrentScore);

    // �����󥹥������O��
    // Set the coin score
    void SetCoinScore(int32 CointScore);

    // �ѥե��`�ޥ󥹥��������O��
    // Set the performance score
    void SetPerformanceScore(int32 PerformanceScore);

    // ���x���������O��
    // Set the distance score
    void SetDistancetScore(int32 DistanceScore);

    // �ᥤ���˥�`�ؑ���ܥ���΄I��
    // Function called when the Main Menu button is pressed
    UFUNCTION()
    void PressMainMenuButton();

protected:
    // ���������å����ɕr�γ��ڻ��I��
    // Called during widget construction
    virtual void NativeConstruct() override;

private:
    // ��������ʾ�åƥ�����
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

    // �ᥤ���˥�`�ܥ���
    // Button to return to the main menu
    UPROPERTY(meta = (Bindwidget))
    class UButton* MainMenuButton;

    // �����`�Ȼ���ؤβ���
    // Reference to the start overlay
    class UStartOverlay* StartOverlay;
};
