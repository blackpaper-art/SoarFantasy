// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartOverlay.generated.h"

/**
 * ================================
 * UStartOverlay
 * ゲーム開始画面の UI ウィジェット
 * UI widget for the game start screen
 * ================================
 */
UCLASS()
class SOARFANTASY_API UStartOverlay : public UUserWidget
{
    GENERATED_BODY()

protected:
    // ウィジェット構築時に呼ばれる
    // Called when the widget is constructed
    virtual void NativeConstruct() override;

private:
    // プレイ開始ボタン
    // Play button
    UPROPERTY(meta = (BindWidget))
    class UButton* PlayButton;

    // プレイ開始ボタン押下時の処理
    // Function called when Play button is pressed
    UFUNCTION()
    void StartGameButton();

    // 終了ボタン
    // Quit button
    UPROPERTY(meta = (BindWidget))
    class UButton* QuitButton;

    // 終了ボタン押下時の処理
    // Function called when Quit button is pressed
    UFUNCTION()
    void QuitGameButton();
};
