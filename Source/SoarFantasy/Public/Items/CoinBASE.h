// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SystemItems/SoarFantasyInterface.h"
#include "CoinBASE.generated.h"

/**
 * ====================================
 * ACoinBASE
 * コイン基本アクター
 * Base actor for collectible coins
 * ====================================
 */
UCLASS()
class SOARFANTASY_API ACoinBASE : public AActor, public ISoarFantasyInterface
{
    GENERATED_BODY()

public:
    // コンストラクタ
    // Constructor
    ACoinBASE();

    // 毎フレーム呼ばれる
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // コインの見た目
    // Visual mesh component for the coin
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
    class UStaticMeshComponent* StaticMeshComp;

    // コインの基本スコア
    // Base score value for the coin
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
    int32 CoinScore = 1;

    // スコア倍率
    // Score multiplier
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
    int32 CoinSocreRate = 1;

    // 磁力フラグ
    // Whether magnet is active
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magnet")
    bool bMagnetActive;

    // 磁力ターゲット位置
    // Target location for magnet attraction
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magnet")
    FVector MagnetCoinTargetLocation;

    // 磁力を有効化
    // Activate magnet effect
    void ActivateMagnet(const FVector& TargetLocation);

    // 磁力を無効化
    // Deactivate magnet effect
    void DeactivateMagnet();

protected:
    // ゲーム開始時に呼ばれる
    // Called when the game starts
    virtual void BeginPlay() override;

    // コイン取得音
    // Sound played when coin is collected
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    class USoundBase* CoinCollectionSound;

    // オーバーラップ開始時の処理
    // Called when overlap begins
    UFUNCTION()
    void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
    // 磁力で移動する速度
    // Speed when magnet is active
    float MagnetCoinSpeed = 1000.f;
};
