// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MissileSpawnerBASE.generated.h"

/**
 * ====================================
 * AMissileSpawnerBASE
 * ミサイル & バフを定期生成するスパウナ
 * Spawner that periodically spawns missiles and buffs
 * ====================================
 */
UCLASS()
class SOARFANTASY_API AMissileSpawnerBASE : public AActor
{
    GENERATED_BODY()

public:
    // コンストラクタ
    // Constructor
    AMissileSpawnerBASE();

protected:
    // ゲーム開始時に呼ばれる
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // ミサイル生成用タイマーハンドル
    // Timer handle for missile spawning
    FTimerHandle MissileSpawnTimerHandle;

    // バフ生成用タイマーハンドル
    // Timer handle for buff spawning
    FTimerHandle BuffSpawnTimerHandle;

    // ミサイル生成の最短時間
    // Minimum spawn interval for missiles
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn")
    float MinTimerCount = 3.f;

    // ミサイル生成の最長時間
    // Maximum spawn interval for missiles
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn")
    float MaxTimerCount = 15.f;

    // 生成するミサイルのBPクラス
    // BP class of missile to spawn
    UPROPERTY(EditAnywhere, Category = "Spawn")
    TSubclassOf<AActor> BPMissile;

    // 生成するバフのBPクラス
    // BP class of buff to spawn
    UPROPERTY(EditAnywhere, Category = "Spawn")
    TSubclassOf<AActor> BPMagnet;

private:
    // ランダムに決定される生成間隔
    // Random spawn interval
    float RandomTimerCount;

    // ミサイルを生成
    // Spawn a missile
    void SpawnMissile();

    // バフを生成
    // Spawn a buff
    void SpawnBuff();
};
