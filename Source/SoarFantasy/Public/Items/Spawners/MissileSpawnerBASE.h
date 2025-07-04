// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MissileSpawnerBASE.generated.h"

/**
 * ====================================
 * AMissileSpawnerBASE
 * ミサイル & バフを協豚伏撹するスパウナ
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
    // ゲ�`ム�_兵�rに柵ばれる
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // ミサイル伏撹喘タイマ�`ハンドル
    // Timer handle for missile spawning
    FTimerHandle MissileSpawnTimerHandle;

    // バフ伏撹喘タイマ�`ハンドル
    // Timer handle for buff spawning
    FTimerHandle BuffSpawnTimerHandle;

    // ミサイル伏撹の恷玉�r�g
    // Minimum spawn interval for missiles
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn")
    float MinTimerCount = 3.f;

    // ミサイル伏撹の恷�L�r�g
    // Maximum spawn interval for missiles
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn")
    float MaxTimerCount = 15.f;

    // 伏撹するミサイルのBPクラス
    // BP class of missile to spawn
    UPROPERTY(EditAnywhere, Category = "Spawn")
    TSubclassOf<AActor> BPMissile;

    // 伏撹するバフのBPクラス
    // BP class of buff to spawn
    UPROPERTY(EditAnywhere, Category = "Spawn")
    TSubclassOf<AActor> BPMagnet;

private:
    // ランダムに�Q協される伏撹�g侯
    // Random spawn interval
    float RandomTimerCount;

    // ミサイルを伏撹
    // Spawn a missile
    void SpawnMissile();

    // バフを伏撹
    // Spawn a buff
    void SpawnBuff();
};
