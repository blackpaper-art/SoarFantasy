// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD/SFHUD.h"
#include "HUD/SFOverlay.h"
#include "HUD/PauseOverlay.h"
#include "HUD/EndOverlay.h"
#include "HUD/StartOverlay.h"
#include "Kismet/GameplayStatics.h"

// �����`�ȥ��`�Щ`�쥤��һ�Ȥ�����ʾ����ե饰���ڻ�
// Initialize flag for showing start overlay only once
bool ASFHUD::bHasShownStartOverlay = false;

// ���`���_ʼ�r�� HUD ���`�Щ`�쥤����ڻ�
// Initialize HUD overlays when the game starts
void ASFHUD::BeginPlay()
{
    Super::BeginPlay();

    UWorld* World = GetWorld();
    if (World)
    {
        APlayerController* Controller = World->GetFirstPlayerController();
        if (Controller && USFOverlayClass)
        {
            // �ᥤ�󥪩`�Щ`�쥤�����ɤ��ƥӥ�`�ݩ`�Ȥ�׷��
            // Create and add main overlay to viewport
            SFOverlay = CreateWidget<USFOverlay>(Controller, USFOverlayClass);
            SFOverlay->AddToViewport();

            // ���ؤΤߥ����`�ȥ��`�Щ`�쥤���ʾ
            // Show start overlay only the first time
            if (!bHasShownStartOverlay)
            {
                OnOffStartOverlay(true);
                Controller->SetShowMouseCursor(true);
                UGameplayStatics::SetGamePaused(GetWorld(), true);

                bHasShownStartOverlay = true;
            }
        }
    }
}

// �ݩ`����˥�`�Υ��󥪥�
// Toggle pause menu on/off
void ASFHUD::OnOffPauseOverlay(bool bOnOff)
{
    if (GetWorld())
    {
        APlayerController* PC = GetWorld()->GetFirstPlayerController();
        if (PC && UPauseOverlayClass)
        {
            PC->SetPause(bOnOff);
            PC->SetShowMouseCursor(bOnOff);
            if (bOnOff)
            {
                PauseOverlay = CreateWidget<UPauseOverlay>(PC, UPauseOverlayClass);
                PauseOverlay->AddToViewport();
            }
            else if (!bOnOff && PauseOverlay)
            {
                PauseOverlay->RemoveFromParent();
                PauseOverlay = nullptr;
            }
        }
    }
}

// ����ɥ�˥�`�Υ��󥪥�
// Toggle end menu on/off
void ASFHUD::OnOffEndOverlay(bool bOnOff)
{
    if (GetWorld())
    {
        APlayerController* PC = GetWorld()->GetFirstPlayerController();
        if (PC && UEndOverlayClass)
        {
            if (bOnOff)
            {
                PC->SetPause(bOnOff);
                if (!EndOverlay)
                {
                    EndOverlay = CreateWidget<UEndOverlay>(PC, UEndOverlayClass);
                }
                if (EndOverlay)
                {
                    EndOverlay->AddToViewport();
                }
            }
        }
    }
}

// �����`�ȥ�˥�`�Υ��󥪥�
// Toggle start menu on/off
void ASFHUD::OnOffStartOverlay(bool bOnOff)
{
    if (GetWorld())
    {
        APlayerController* PC = GetWorld()->GetFirstPlayerController();
        if (PC && UStartOverlayClass)
        {
            PC->SetShowMouseCursor(bOnOff);
            PC->SetPause(bOnOff);

            if (bOnOff)
            {
                if (!StartOverlay)
                {
                    StartOverlay = CreateWidget<UStartOverlay>(PC, UStartOverlayClass);
                }
                if (StartOverlay && !StartOverlay->IsInViewport())
                {
                    StartOverlay->AddToViewport();
                }
            }
            else
            {
                if (StartOverlay)
                {
                    StartOverlay->RemoveFromParent();
                    StartOverlay = nullptr;
                }
            }
        }
    }
}
