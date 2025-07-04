// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/Spawners/MissileSpawnerBASE.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"

// ================================
// AMissileSpawnerBASE
// ミサイル�Ε丱佞良�撹砿尖クラス
// Class for managing missile and buff spawning
// ================================

// コンストラクタ
// Constructor
AMissileSpawnerBASE::AMissileSpawnerBASE()
{
    // Tick は聞喘しない
    // Tick is not needed
    PrimaryActorTick.bCanEverTick = false;
}

// ゲ�`ム�_兵�rにタイマ�`を�O協
// Set up timers when the game starts
void AMissileSpawnerBASE::BeginPlay()
{
    Super::BeginPlay();

    // ミサイル伏撹の�g侯をランダムに�Q協
    // Randomize missile spawn interval
    RandomTimerCount = FMath::RandRange(MinTimerCount, MaxTimerCount);

    // ミサイル伏撹タイマ�`を軟��
    // Start missile spawn timer
    GetWorldTimerManager().SetTimer(
        MissileSpawnTimerHandle,
        this,
        &AMissileSpawnerBASE::SpawnMissile,
        RandomTimerCount,
        true
    );

    // バフ伏撹タイマ�`を軟�咤┨牟�30昼�g侯��
    // Start buff spawn timer (fixed 30 seconds)
    GetWorldTimerManager().SetTimer(
        BuffSpawnTimerHandle,
        this,
        &AMissileSpawnerBASE::SpawnBuff,
        30,
        true
    );
}

// ミサイルを伏撹する
// Spawn a missile actor
void AMissileSpawnerBASE::SpawnMissile()
{
    // プレイヤ�`を函誼
    // Get player pawn
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (!PlayerPawn)
    {
        return;
    }

    // 伏撹了崔を��麻�┘廛譽ぅ筴`Z + 200��
    // Calculate spawn location (player Z + 200)
    FVector MyLocation = GetActorLocation();
    float PlayerZ = PlayerPawn->GetActorLocation().Z + 200.f;

    // プレイヤ�`圭�鬚鯱鬚�
    // Rotate to face player direction
    FRotator PlayerRotator = FRotator(0, 180, 0);

    FVector SpawnLocation = FVector(MyLocation.X, MyLocation.Y, PlayerZ);

    // ミサイルを伏撹
    // Spawn missile actor
    GetWorld()->SpawnActor<AActor>(BPMissile, SpawnLocation, PlayerRotator);
}

// バフを伏撹する
// Spawn a buff actor
void AMissileSpawnerBASE::SpawnBuff()
{
    // プレイヤ�`を函誼
    // Get player pawn
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (!PlayerPawn)
    {
        return;
    }

    // 伏撹了崔を��麻�┘廛譽ぅ筴`Z��
    // Calculate spawn location (player Z)
    FVector MyLocation = GetActorLocation();
    float PlayerZ = PlayerPawn->GetActorLocation().Z;

    // プレイヤ�`圭�鬚鯱鬚�
    // Rotate to face player direction
    FRotator PlayerRotator = FRotator(0, 180, 0);

    FVector SpawnLocation = FVector(MyLocation.X, MyLocation.Y, PlayerZ);

    // バフを伏撹
    // Spawn buff actor
    GetWorld()->SpawnActor<AActor>(BPMagnet, SpawnLocation, PlayerRotator);
}
