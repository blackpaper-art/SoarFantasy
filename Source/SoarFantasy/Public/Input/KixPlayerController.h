// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "KixPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class ACharactersKix;

/**
 * ====================================
 * AKixPlayerController
 * プレイヤー操作を管理するコントローラ
 * Player controller for handling player input
 * ====================================
 */

 // ポーズメニュー状態の列挙型
 // Enum for pause menu UI state
UENUM(BlueprintType)
enum class EPauseUIState : uint8
{
    None UMETA(DisplayName = "None"),
    MainMenu UMETA(DisplayName = "Pause Main"),
    SubMenu UMETA(DisplayName = "Other Menu"),
};

UCLASS()
class SOARFANTASY_API AKixPlayerController : public APlayerController
{
    GENERATED_BODY()
public:
    // 入力コンポーネントをセットアップ
    // Setup input component bindings
    virtual void SetupInputComponent() override;

    // 現在使用する Input Mapping Context
    // Current input mapping context
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    TObjectPtr<UInputMappingContext> CurrentMappingContext;

    // ジャンプアクション
    // Jump action
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    TObjectPtr<UInputAction> JumpAction;

    // しゃがむアクション
    // Down action
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    TObjectPtr<UInputAction> DownAction;

    // ダッシュアクション
    // Dash action
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    TObjectPtr<UInputAction> DashAction;

    // ポーズアクション
    // Pause action
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    TObjectPtr<UInputAction> PauseAction;

    // 現在操作しているキャラクター
    // Currently possessed character
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    TObjectPtr<ACharactersKix> CurrentChara;

    // ポーズ状態を初期化
    // Reset pause flags
    void SetPauseBoolFalse();

    // 現在のポーズメニュー状態
    // Current pause menu UI state
    EPauseUIState CurrentPauseUIState = EPauseUIState::None;

protected:
    // ポーン所有時に呼ばれる
    // Called when possessing a pawn
    virtual void OnPossess(APawn* InPawn) override;

    // ジャンプ処理
    // Handle jump input
    void Jump();

    // ポーズ処理
    // Handle pause input
    void PauseGame();

    // しゃがむ処理
    // Handle down input
    void Down();

    // ダッシュ処理
    // Handle dash input
    void Dash();

private:
    // ポーズメニューがアクティブかどうか
    // Whether pause menu is active
    bool bPauseMenuActivating = false;
};
