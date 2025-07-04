// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SystemItems/SoarFantasyInterface.h"
#include "CoinBASE.generated.h"

/**
 * ====================================
 * ACoinBASE
 * コイン児云アクタ�`
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

    // �哀侫讒`ム柵ばれる
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // コインの��た朕
    // Visual mesh component for the coin
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
    class UStaticMeshComponent* StaticMeshComp;

    // コインの児云スコア
    // Base score value for the coin
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
    int32 CoinScore = 1;

    // スコア蔚楕
    // Score multiplier
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
    int32 CoinSocreRate = 1;

    // 甘薦フラグ
    // Whether magnet is active
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magnet")
    bool bMagnetActive;

    // 甘薦タ�`ゲット了崔
    // Target location for magnet attraction
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magnet")
    FVector MagnetCoinTargetLocation;

    // 甘薦を嗤�浸�
    // Activate magnet effect
    void ActivateMagnet(const FVector& TargetLocation);

    // 甘薦を�o�浸�
    // Deactivate magnet effect
    void DeactivateMagnet();

protected:
    // ゲ�`ム�_兵�rに柵ばれる
    // Called when the game starts
    virtual void BeginPlay() override;

    // コイン函誼咄
    // Sound played when coin is collected
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    class USoundBase* CoinCollectionSound;

    // オ�`バ�`ラップ�_兵�rの�I尖
    // Called when overlap begins
    UFUNCTION()
    void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
    // 甘薦で卞�咾垢詼拔�
    // Speed when magnet is active
    float MagnetCoinSpeed = 1000.f;
};
