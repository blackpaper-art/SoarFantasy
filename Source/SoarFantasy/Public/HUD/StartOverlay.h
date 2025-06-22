// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartOverlay.generated.h"

/**
 * ================================
 * UStartOverlay
 * ���`���_ʼ����� UI ���������å�
 * UI widget for the game start screen
 * ================================
 */
UCLASS()
class SOARFANTASY_API UStartOverlay : public UUserWidget
{
    GENERATED_BODY()

protected:
    // ���������åȘ��B�r�˺��Ф��
    // Called when the widget is constructed
    virtual void NativeConstruct() override;

private:
    // �ץ쥤�_ʼ�ܥ���
    // Play button
    UPROPERTY(meta = (BindWidget))
    class UButton* PlayButton;

    // �ץ쥤�_ʼ�ܥ���Ѻ�r�΄I��
    // Function called when Play button is pressed
    UFUNCTION()
    void StartGameButton();

    // �K�˥ܥ���
    // Quit button
    UPROPERTY(meta = (BindWidget))
    class UButton* QuitButton;

    // �K�˥ܥ���Ѻ�r�΄I��
    // Function called when Quit button is pressed
    UFUNCTION()
    void QuitGameButton();
};
