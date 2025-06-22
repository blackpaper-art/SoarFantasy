// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapSpawnerBASE.generated.h"

/**
 * ====================================
 * AMapSpawnerBASE
 * マップ生成用の基底クラス
 * Base class for procedural map spawning
 * ====================================
 */
UCLASS()
class SOARFANTASY_API AMapSpawnerBASE : public AActor
{
    GENERATED_BODY()

public:
    // コンストラクタ
    // Constructor
    AMapSpawnerBASE();

protected:
    // ゲーム開始時に呼ばれる
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // マップデータテーブル（エディタでバインド）
    // Data table pointer to read map data (bind in Editor)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map")
    UDataTable* MapDataTable;

    // プラットフォーム・障害物生成に使う GroundBASE ブループリント
    // GroundBASE blueprint used to spawn platforms and obstacles (e.g., BP_Ground)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
    TSubclassOf<class AGroundBASE> GroundBP;

    // マップ生成基準位置（この Actor の位置を推奨）
    // Base location for map generation (usually this Actor's position)
    UPROPERTY(EditAnywhere, Category = "Map")
    FVector BaseLocation;

    // プラットフォームのサイズ（幅, 奥行き, 高さ）
    // Size of platform (Width, Depth, Height), default (200, 500, 500)
    UPROPERTY(EditAnywhere, Category = "Map")
    FVector PlatformSize = FVector(200.f, 500.f, 500.f);

    // プラットフォームが無い場合の間隔
    // Gap width when no platform exists, default 200
    UPROPERTY(EditAnywhere, Category = "Map")
    float GapWidth = 200.f;

    // データテーブルからマップを生成
    // Generate map based on DataTable
    void GenerateMap();

public:
    // Tick 関数（オプション）
    // Tick function (optional)
    virtual void Tick(float DeltaTime) override;
};
