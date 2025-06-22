// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/Spawners/MapSpawnerBASE.h"
#include "Items/GroundBASE.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Items/Spawners/MapDataRow.h"
#include "Kismet/GameplayStatics.h"

// ================================
// AMapSpawnerBASE
// マップ生成の基底クラス
// Base class for procedural map generation
// ================================

// コンストラクタ：初期位置を保存
// Constructor: save base location
AMapSpawnerBASE::AMapSpawnerBASE()
{
    PrimaryActorTick.bCanEverTick = false;
    BaseLocation = GetActorLocation();
}

// ゲーム開始時にマップ生成を呼び出す
// Call map generation when the game starts
void AMapSpawnerBASE::BeginPlay()
{
    Super::BeginPlay();
    GenerateMap();
}

// Tick は未使用
// Tick not used
void AMapSpawnerBASE::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// マップ生成メイン処理
// Main logic for generating the map
void AMapSpawnerBASE::GenerateMap()
{
    if (!MapDataTable)
    {
        UE_LOG(LogTemp, Error, TEXT("MapDataTable is not assigned."));
        return;
    }

    // データテーブルから全行取得
    // Get all rows from data table
    static const FString ContextString(TEXT("MapData"));
    TArray<FMapDataRow*> AllRows;
    MapDataTable->GetAllRows<FMapDataRow>(ContextString, AllRows);

    // X軸初期値（横方向の開始位置）
    // Initial X position
    float CurrentX = BaseLocation.X;

    // Y軸は固定値
    // Y position is fixed
    float FixedY = BaseLocation.Y;

    for (FMapDataRow* Row : AllRows)
    {
        if (!Row)
        {
            continue;
        }

        // 各レイヤー文字列を取得 & トリム
        // Get and trim each layer string
        FString PlatformStr = Row->Platform_Layer.TrimStartAndEnd();
        FString EnemyStr = Row->Enemy_Layer.TrimStartAndEnd();
        FString CoinStr = Row->Coin_Layer.TrimStartAndEnd();
        FString AirStr = Row->Air_Layer.TrimStartAndEnd();

        // 生成座標を計算：Xは累積値、Yは固定、Zはプラットフォームの高さ
        // Calculate spawn position: X = current, Y = fixed, Z = platform height
        float SpawnX = CurrentX;
        float SpawnY = FixedY;
        float BaseZ = BaseLocation.Z;
        float PlatformZ = BaseZ;

        AGroundBASE* PlatformActor = nullptr;

        // プラットフォーム生成処理
        // Platform generation
        if (!PlatformStr.IsEmpty())
        {
            int32 PlatformValue = FCString::Atoi(*PlatformStr);
            int32 ParsedPlatformStyle = PlatformValue / 10;
            int32 HeightLevel = PlatformValue % 10;
            float HeightMultiplier = 1.f + HeightLevel * 0.1f;
            PlatformZ = BaseZ * HeightMultiplier;

            FVector SpawnLocation(SpawnX, SpawnY, PlatformZ);
            FRotator SpawnRotation = FRotator::ZeroRotator;
            FTransform SpawnTransform(SpawnRotation, SpawnLocation);

            // ディファード生成で各プロパティ設定
            // Deferred spawn to set properties before BeginPlay
            PlatformActor = GetWorld()->SpawnActorDeferred<AGroundBASE>(GroundBP, SpawnTransform);
            if (PlatformActor)
            {
                PlatformActor->PlatformStyle = ParsedPlatformStyle;

                // コイン設定
                // Coin setup
                if (!CoinStr.IsEmpty())
                {
                    int32 CoinValue = FCString::Atoi(*CoinStr);
                    int32 ParsedCoinStyle = CoinValue / 10;
                    int32 ParsedCoinCount = CoinValue % 10;
                    PlatformActor->CoinStyle = ParsedCoinStyle;
                    PlatformActor->CoinCount = ParsedCoinCount;
                }

                // 敵設定
                // Enemy setup
                if (!EnemyStr.IsEmpty())
                {
                    int32 EnemyValue = FCString::Atoi(*EnemyStr);
                    if (EnemyValue != 0 && PlatformActor)
                    {
                        PlatformActor->EnemyTypeNum = EnemyValue;
                    }
                }

                // 生成完了
                // Finish spawning
                UGameplayStatics::FinishSpawningActor(PlatformActor, SpawnTransform);
            }
        }

        // 空中障害物生成
        // Aerial obstacle generation
        if (!AirStr.IsEmpty())
        {
            int32 ObstacleStyle = FCString::Atoi(*AirStr);
            float ObstacleZ = (PlatformActor ? PlatformZ : BaseZ) + 1000.f;
            FVector ObstacleLocation(SpawnX, SpawnY, ObstacleZ);
            FRotator ObstacleRotation = FRotator::ZeroRotator;

            AGroundBASE* ObstacleActor = GetWorld()->SpawnActor<AGroundBASE>(GroundBP, ObstacleLocation, ObstacleRotation);
            if (ObstacleActor)
            {
                ObstacleActor->ObstacleStyle = ObstacleStyle;
                // Blueprint で ObstacleStyle に応じて処理を分岐
                // Handle specifics in Blueprint using ObstacleStyle
            }
        }

        // X位置を更新：プラットフォーム幅またはGapWidth
        // Update X position: platform width or gap width
        if (!PlatformStr.IsEmpty())
        {
            CurrentX += PlatformSize.X;
        }
        else
        {
            CurrentX += GapWidth;
        }
    }
}
