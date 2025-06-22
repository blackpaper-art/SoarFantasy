// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GroundBASE.generated.h"

/**
 * ====================================
 * AGroundBASE
 * プラットフォームの基本アクター
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

    // 毎フレームの更新
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // プラットフォームの見た目
    // Visual mesh for the platform
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
    class UStaticMeshComponent* StaticMeshComp;

    // 衝突判定用ボックス
    // Collision box component
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
    class UBoxComponent* BoxCollisionComp;

    // 移動速度倍率
    // Platform move speed multiplier
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float PlatformMoveSpeedRate = 1.f;

    // 地面の Y 位置
    // Ground position Y
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location", meta = (ExposeOnSpawn = "true"))
    float GroundPostionY;

    // スポーン位置
    // Spawn location
    FVector SpawnLocation;

    // 実際の地面位置
    // Actual ground location
    FVector GroundLocation;

    // コイン生成用クラス
    // Coin actor class
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
    TSubclassOf<AActor> CoinClass;

    // コインの数
    // Number of coins
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin", meta = (ExposeOnSpawn = "true"))
    int32 CoinCount = 5;

    // コインの間隔
    // Spacing between coins
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
    float CoinSpacing = 80.f;

    // コインコンポーネント配列
    // Array of coin child components
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
    TArray<UChildActorComponent*> CoinComponents;

    // プラットフォームのスタイル
    // Platform style ID
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style")
    int32 PlatformStyle = 0;

    // コインのスタイル
    // Coin style ID
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
    int32 CoinStyle = 0;

    // 障害物のスタイル
    // Obstacle style ID
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle")
    int32 ObstacleStyle = 0;

    // 敵（球体）のクラス
    // Enemy sphere class
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
    TSubclassOf<AActor> EnemySphereClass;

    // 敵（コーン型）のクラス
    // Enemy cone class
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
    TSubclassOf<AActor> EnemyConeClass;

    // 敵タイプ番号
    // Enemy type number
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy", meta = (ExposeOnSpawn = "true"))
    int32 EnemyTypeNum = 0;

    // 敵コンポーネント配列
    // Array of enemy child components
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
    TArray<UChildActorComponent*> EnemyComponents;

protected:
    // ゲーム開始時の初期化
    // Called when the game starts
    virtual void BeginPlay() override;

private:
    // 基本移動速度
    // Base move speed
    float PlatformMoveSpeedBase = -600.f;

    // 現在の移動速度
    // Current move speed
    float PlatformCurrentSpeed;
};
