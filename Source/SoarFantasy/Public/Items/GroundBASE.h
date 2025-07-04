// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GroundBASE.generated.h"

/**
 * ====================================
 * AGroundBASE
 * プラットフォ�`ムの児云アクタ�`
 * Base actor for moving platforms with coins and enemies
 * ====================================
 */
UCLASS()
class SOARFANTASY_API AGroundBASE : public AActor
{
    GENERATED_BODY()

public:
    // コンストラクタ
    // Constructor
    AGroundBASE();

    // �哀侫讒`ムの厚仟
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // プラットフォ�`ムの��た朕
    // Visual mesh for the platform
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
    class UStaticMeshComponent* StaticMeshComp;

    // �n融登協喘ボックス
    // Collision box component
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
    class UBoxComponent* BoxCollisionComp;

    // 卞�嗚拔髪饗�
    // Platform move speed multiplier
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float PlatformMoveSpeedRate = 1.f;

    // 仇中の Y 了崔
    // Ground position Y
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location", meta = (ExposeOnSpawn = "true"))
    float GroundPostionY;

    // スポ�`ン了崔
    // Spawn location
    FVector SpawnLocation;

    // �g�Hの仇中了崔
    // Actual ground location
    FVector GroundLocation;

    // コイン伏撹喘クラス
    // Coin actor class
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
    TSubclassOf<AActor> CoinClass;

    // コインの方
    // Number of coins
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin", meta = (ExposeOnSpawn = "true"))
    int32 CoinCount = 5;

    // コインの�g侯
    // Spacing between coins
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
    float CoinSpacing = 80.f;

    // コインコンポ�`ネント塘双
    // Array of coin child components
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
    TArray<UChildActorComponent*> CoinComponents;

    // プラットフォ�`ムのスタイル
    // Platform style ID
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style")
    int32 PlatformStyle = 0;

    // コインのスタイル
    // Coin style ID
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
    int32 CoinStyle = 0;

    // 嬾墾麗のスタイル
    // Obstacle style ID
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle")
    int32 ObstacleStyle = 0;

    // �械�白悶��のクラス
    // Enemy sphere class
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
    TSubclassOf<AActor> EnemySphereClass;

    // �械┘芥`ン侏��のクラス
    // Enemy cone class
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
    TSubclassOf<AActor> EnemyConeClass;

    // �灰織ぅ弖�催
    // Enemy type number
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy", meta = (ExposeOnSpawn = "true"))
    int32 EnemyTypeNum = 0;

    // �灰灰鵐櫞`ネント塘双
    // Array of enemy child components
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
    TArray<UChildActorComponent*> EnemyComponents;

protected:
    // ゲ�`ム�_兵�rの兜豚晒
    // Called when the game starts
    virtual void BeginPlay() override;

private:
    // 児云卞�嗚拔�
    // Base move speed
    float PlatformMoveSpeedBase = -600.f;

    // �F壓の卞�嗚拔�
    // Current move speed
    float PlatformCurrentSpeed;
};
