// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SFHUD.generated.h"

/**
 * ====================================
 * ASFHUD
 * ���`���� HUD �����饹
 * In-game HUD manager class
 * ====================================
 */
UCLASS()
class SOARFANTASY_API ASFHUD : public AHUD
{
    GENERATED_BODY()

protected:
    // ���`���_ʼ�r�˺��Ф��
    // Called when the game starts
    virtual void BeginPlay() override;

private:
    // �ᥤ�� HUD ���`�Щ`�쥤 ���饹
    // Main gameplay overlay class
    UPROPERTY(EditDefaultsOnly, Category = "SoarFantasy")
    TSubclassOf<class USFOverlay> USFOverlayClass;

    // �ᥤ�� HUD ���`�Щ`�쥤 ���󥹥���
    // Main gameplay overlay instance
    UPROPERTY(EditDefaultsOnly, Category = "SoarFantasy")
    USFOverlay* SFOverlay;

    // �ݩ`����˥�` ���饹
    // Pause menu overlay class
    UPROPERTY(EditDefaultsOnly, Category = "PauseMenu")
    TSubclassOf<class UPauseOverlay> UPauseOverlayClass;

    // �ݩ`����˥�` ���󥹥���
    // Pause menu overlay instance
    UPROPERTY(EditDefaultsOnly, Category = "PauseMenu")
    UPauseOverlay* PauseOverlay;

    // ����ɥ�˥�` ���饹
    // End game menu overlay class
    UPROPERTY(EditDefaultsOnly, Category = "EndMenu")
    TSubclassOf<class UEndOverlay> UEndOverlayClass;

    // ����ɥ�˥�` ���󥹥���
    // End game menu overlay instance
    UPROPERTY(EditDefaultsOnly, Category = "EndMenu")
    UEndOverlay* EndOverlay;

    // �����`�ȥ�˥�` ���饹
    // Start menu overlay class
    UPROPERTY(EditDefaultsOnly, Category = "StartMenu")
    TSubclassOf<class UStartOverlay> UStartOverlayClass;

    // �����`�ȥ�˥�` ���󥹥���
    // Start menu overlay instance
    UPROPERTY(EditDefaultsOnly, Category = "StartMenu")
    UStartOverlay* StartOverlay;

public:
    // �ᥤ�� HUD ���`�Щ`�쥤��ȡ��
    // Get main overlay
    FORCEINLINE USFOverlay* GetSFOverlay() const { return SFOverlay; }

    // ����ɥ��`�Щ`�쥤��ȡ��
    // Get end overlay
    FORCEINLINE UEndOverlay* GetEndOverlay() const { return EndOverlay; }

    // �����`�ȥ��`�Щ`�쥤��ȡ��
    // Get start overlay
    FORCEINLINE UStartOverlay* GetStartOverlay() const { return StartOverlay; }

    // �ݩ`����˥�`��ʾ���Ф��椨
    // Toggle pause menu overlay
    void OnOffPauseOverlay(bool bOnOff);

    // ����ɥ�˥�`��ʾ���Ф��椨
    // Toggle end menu overlay
    void OnOffEndOverlay(bool bOnOff);

    // �����`�ȥ�˥�`��ʾ���Ф��椨
    // Toggle start menu overlay
    void OnOffStartOverlay(bool bOnOff);

    // �����`�ȥ�˥�`��һ�Ȥ�����ʾ����ե饰
    // Flag to show start overlay only once
    static bool bHasShownStartOverlay;
};
