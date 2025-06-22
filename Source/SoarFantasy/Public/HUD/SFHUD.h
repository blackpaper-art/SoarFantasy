// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SFHUD.generated.h"

/**
 * ====================================
 * ASFHUD
 * ゲーム内 HUD 管理クラス
 * In-game HUD manager class
 * ====================================
 */
UCLASS()
class SOARFANTASY_API ASFHUD : public AHUD
{
    GENERATED_BODY()

protected:
    // ゲーム開始時に呼ばれる
    // Called when the game starts
    virtual void BeginPlay() override;

private:
    // メイン HUD オーバーレイ クラス
    // Main gameplay overlay class
    UPROPERTY(EditDefaultsOnly, Category = "SoarFantasy")
    TSubclassOf<class USFOverlay> USFOverlayClass;

    // メイン HUD オーバーレイ インスタンス
    // Main gameplay overlay instance
    UPROPERTY(EditDefaultsOnly, Category = "SoarFantasy")
    USFOverlay* SFOverlay;

    // ポーズメニュー クラス
    // Pause menu overlay class
    UPROPERTY(EditDefaultsOnly, Category = "PauseMenu")
    TSubclassOf<class UPauseOverlay> UPauseOverlayClass;

    // ポーズメニュー インスタンス
    // Pause menu overlay instance
    UPROPERTY(EditDefaultsOnly, Category = "PauseMenu")
    UPauseOverlay* PauseOverlay;

    // エンドメニュー クラス
    // End game menu overlay class
    UPROPERTY(EditDefaultsOnly, Category = "EndMenu")
    TSubclassOf<class UEndOverlay> UEndOverlayClass;

    // エンドメニュー インスタンス
    // End game menu overlay instance
    UPROPERTY(EditDefaultsOnly, Category = "EndMenu")
    UEndOverlay* EndOverlay;

    // スタートメニュー クラス
    // Start menu overlay class
    UPROPERTY(EditDefaultsOnly, Category = "StartMenu")
    TSubclassOf<class UStartOverlay> UStartOverlayClass;

    // スタートメニュー インスタンス
    // Start menu overlay instance
    UPROPERTY(EditDefaultsOnly, Category = "StartMenu")
    UStartOverlay* StartOverlay;

public:
    // メイン HUD オーバーレイを取得
    // Get main overlay
    FORCEINLINE USFOverlay* GetSFOverlay() const { return SFOverlay; }

    // エンドオーバーレイを取得
    // Get end overlay
    FORCEINLINE UEndOverlay* GetEndOverlay() const { return EndOverlay; }

    // スタートオーバーレイを取得
    // Get start overlay
    FORCEINLINE UStartOverlay* GetStartOverlay() const { return StartOverlay; }

    // ポーズメニュー表示の切り替え
    // Toggle pause menu overlay
    void OnOffPauseOverlay(bool bOnOff);

    // エンドメニュー表示の切り替え
    // Toggle end menu overlay
    void OnOffEndOverlay(bool bOnOff);

    // スタートメニュー表示の切り替え
    // Toggle start menu overlay
    void OnOffStartOverlay(bool bOnOff);

    // スタートメニューを一度だけ表示するフラグ
    // Flag to show start overlay only once
    static bool bHasShownStartOverlay;
};
