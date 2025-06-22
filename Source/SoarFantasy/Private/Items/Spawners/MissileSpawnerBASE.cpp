// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/Spawners/MissileSpawnerBASE.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"

// ================================
// AMissileSpawnerBASE
// ミサイル＆バフの生成管理クラス
// Class for managing missile and buff spawning
// ================================

// コンストラクタ
// Constructor
AMissileSpawnerBASE::AMissileSpawnerBASE()
{
    // Tick は使用しない
    // Tick is not needed
    PrimaryActorTick.bCanEverTick = false;
}

// ゲーム開始時にタイマーを設定
// Set up timers when the game starts
void AMissileSpawnerBASE::BeginPlay()
{
    Super::BeginPlay();

    // ミサイル生成の間隔をランダムに決定
    // Randomize missile spawn interval
    RandomTimerCount = FMath::RandRange(MinTimerCount, MaxTimerCount);

    // ミサイル生成タイマーを起動
    // Start missile spawn timer
    GetWorldTimerManager().SetTimer(
        MissileSpawnTimerHandle,
        this,
        &AMissileSpawnerBASE::SpawnMissile,
        RandomTimerCount,
        true
    );

    // バフ生成タイマーを起動（固定30秒間隔）
    // Start buff spawn timer (fixed 30 seconds)
    GetWorldTimerManager().SetTimer(
        BuffSpawnTimerHandle,
        this,
        &AMissileSpawnerBASE::SpawnBuff,
        30,
        true
    );
}

// ミサイルを生成する
// Spawn a missile actor
void AMissileSpawnerBASE::SpawnMissile()
{
    // プレイヤーを取得
    // Get player pawn
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (!PlayerPawn)
    {
        return;
    }

    // 生成位置を計算（プレイヤーZ + 200）
    // Calculate spawn location (player Z + 200)
    FVector MyLocation = GetActorLocation();
    float PlayerZ = PlayerPawn->GetActorLocation().Z + 200.f;

    // プレイヤー方向を向く
    // Rotate to face player direction
    FRotator PlayerRotator = FRotator(0, 180, 0);

    FVector SpawnLocation = FVector(MyLocation.X, MyLocation.Y, PlayerZ);

    // ミサイルを生成
    // Spawn missile actor
    GetWorld()->SpawnActor<AActor>(BPMissile, SpawnLocation, PlayerRotator);
}

// バフを生成する
// Spawn a buff actor
void AMissileSpawnerBASE::SpawnBuff()
{
    // プレイヤーを取得
    // Get player pawn
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (!PlayerPawn)
    {
        return;
    }

    // 生成位置を計算（プレイヤーZ）
    // Calculate spawn location (player Z)
    FVector MyLocation = GetActorLocation();
    float PlayerZ = PlayerPawn->GetActorLocation().Z;

    // プレイヤー方向を向く
    // Rotate to face player direction
    FRotator PlayerRotator = FRotator(0, 180, 0);

    FVector SpawnLocation = FVector(MyLocation.X, MyLocation.Y, PlayerZ);

    // バフを生成
    // Spawn buff actor
    GetWorld()->SpawnActor<AActor>(BPMagnet, SpawnLocation, PlayerRotator);
}
