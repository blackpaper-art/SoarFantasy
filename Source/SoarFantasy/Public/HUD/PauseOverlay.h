// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseOverlay.generated.h"

/**
 * ====================================
 * UPauseOverlay
 * �ݩ`����˥�` UI ���������å�
 * UI widget for pause menu
 * ====================================
 */
UCLASS()
class SOARFANTASY_API UPauseOverlay : public UUserWidget
{
    GENERATED_BODY()

protected:
    // ���������åȘ��B�r�˺��Ф��
    // Called when widget is constructed
    virtual void NativeConstruct() override;

private:
    // ���`�����_�ܥ���
    // Resume button
    UPROPERTY(meta = (BindWidget))
    class UButton* ResumeButton;

    // �ᥤ���˥�`�ܥ��󣨌g�H�ˤϽK�˥�˥�`���_����
    // Main menu button (opens end overlay)
    UPROPERTY(meta = (BindWidget))
    class UButton* MainMenuButton;

    // ���_�ܥ���Ѻ�r�΄I��
    // Function called when Resume button is clicked
    UFUNCTION()
    void ResumeButtonClicked();

    // �ᥤ���˥�`�ܥ���Ѻ�r�΄I��
    // Function called when Main Menu button is clicked
    UFUNCTION()
    void EndButtonClicked();

    // �����ã�HUD�ڤΥ��`�Щ`�쥤
    // Reference to HUD overlays
    UPROPERTY()
    class USFOverlay* SFOverlay;

    UPROPERTY()
    class UEndOverlay* EndOverlay;
};
