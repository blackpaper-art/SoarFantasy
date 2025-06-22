// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseOverlay.generated.h"

/**
 * ====================================
 * UPauseOverlay
 * ポーズメニュー UI ウィジェット
 * UI widget for pause menu
 * ====================================
 */
UCLASS()
class SOARFANTASY_API UPauseOverlay : public UUserWidget
{
    GENERATED_BODY()

protected:
    // ウィジェット構築時に呼ばれる
    // Called when widget is constructed
    virtual void NativeConstruct() override;

private:
    // ゲーム再開ボタン
    // Resume button
    UPROPERTY(meta = (BindWidget))
    class UButton* ResumeButton;

    // メインメニューボタン（実際には終了メニューを開く）
    // Main menu button (opens end overlay)
    UPROPERTY(meta = (BindWidget))
    class UButton* MainMenuButton;

    // 再開ボタン押下時の処理
    // Function called when Resume button is clicked
    UFUNCTION()
    void ResumeButtonClicked();

    // メインメニューボタン押下時の処理
    // Function called when Main Menu button is clicked
    UFUNCTION()
    void EndButtonClicked();

    // 参照用：HUD内のオーバーレイ
    // Reference to HUD overlays
    UPROPERTY()
    class USFOverlay* SFOverlay;

    UPROPERTY()
    class UEndOverlay* EndOverlay;
};
