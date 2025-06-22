// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/CharactersBASE.h"
#include "SystemItems/SoarFantasyInterface.h"

#include "CharactersKix.generated.h"

/**
 * ====================================
 * ACharactersKix
 * プレイヤーキャラクターのメインクラス
 * Main player character class for SoarFantasy
 * ====================================
 */
UCLASS()
class SOARFANTASY_API ACharactersKix : public ACharactersBASE, public ISoarFantasyInterface
{
    GENERATED_BODY()

public:
    // コンストラクタ
    // Constructor
    ACharactersKix();

    // 毎フレーム更新
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // コインのマグネット処理を更新
    // Update coin magnet effect
    void UpdateMakeCoinMovetoPlayer();

    // コインスコアを加算
    // Add coin score
    void AddCoinScore(int32 Score);

    // 入力: ジャンプ
    // Input: Jump
    virtual void Jump() override;

    // 着地時の処理
    // Called on landing
    virtual void Landed(const FHitResult& Hit) override;

    // 入力: ダウン
    // Input: Down
    void Down();

    // 入力: ダッシュ（未実装）
    // Input: Dash (placeholder)
    void Dash();

    // マグネットを有効化
    // Activate magnet power-up
    void ActiveKixsMag();

    // ビジュアル: カメラ関連
    // Visual: Camera and spring arm
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
    class USpringArmComponent* SpringArm;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
    class UCameraComponent* MainPlatformCamera;

    // 動き関連: ダブルジャンプ
    // Movement: Double jump flag
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump")
    bool bDoingDoubleJump = false;

    UFUNCTION(BlueprintCallable)
    void MakeStuck(bool bStuck) { bIsStuck = bStuck; }

    // アニメーション
    // Animation
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
    class UAnimMontage* JumpMontage;

    // スコア系
    // Scoring
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
    float MaxCoinBarValue = 1000.f;

    int32 GetPlayerCurrentScore() const { return CurrentScore; }
    int32 GetPlayerCoinScoreScore() const { return CoinScore; }
    int32 GetPlayerPerformanceScore() const { return PerformanceScore; }
    int32 GetPlayerDistanceScore() const { return DistanceScore; }

    // 距離スコア加算用タイマー
    // Timer handle for distance scoring
    FTimerHandle AddDistanceScoreHandle;

    // ポーズメニューを開閉
    // Open/close pause menu
    void OpenOrClosePauseGameMenu(bool bPauseMenuActivating);

    bool GetOtherOverlayActivating() const { return bOtherOverlayIsActivated; };

    // エンドメニューを開く
    // Open end menu
    void OpenEndMenu();

    // 死亡時処理
    // Called when player dies
    UFUNCTION(BlueprintCallable)
    void KixDead();

    // データレイヤー
    // Level data layers
    UPROPERTY(EditAnywhere, Category = "DataLayer")
    class UDataLayerAsset* MainLevelLayerAsset;

    UPROPERTY(EditAnywhere, Category = "DataLayer")
    class UDataLayerAsset* BonusLevelLayerAsset;

protected:
    virtual void BeginPlay() override;

    // データレイヤー切替
    void SwitchToNormalMap();
    void SwitchToBonusMap();

    // 死亡時音
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    class USoundBase* DeadSound;

private:
    // HUD初期化
    void InitializeSFOverlay();

    // HUDオーバーレイ
    UPROPERTY()
    class USFOverlay* SFOverlay;

    UPROPERTY()
    class UPauseOverlay* PauseOverlay;

    UPROPERTY()
    class UEndOverlay* EndOverlay;

    bool bOtherOverlayIsActivated = false;

    // ボーナスタイマー
    FTimerHandle SetBonusTimeHandle;
    bool bBonusTime = false;

    void SetBonusTimeTrue();
    void SetBonusTimeFalse();

    // スコア内部変数
    float BarPercent;
    float BarCurrentScore;
    int32 CoinScore = 0;
    int32 DistanceScore = 0;
    int32 PerformanceScore = 0;
    int32 CurrentScore = 0;

    void AddDistanceScore();

    // マグネット
    FTimerHandle MagnetTimerHandle;
    bool bMagnetActive = false;
    float MagnetRadius = 500.f;
    void DeactivateKixsMag();

    // 動き
    FVector StartLocation;
    FVector CurrentLocation;
    bool bIsStuck = false;
    bool bIsDash = false;
};
