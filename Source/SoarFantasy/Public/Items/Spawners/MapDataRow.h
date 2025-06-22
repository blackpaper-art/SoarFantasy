// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MapDataRow.generated.h"

/**
 * ================================
 * FMapDataRow
 * マップ生成用のデータテーブル行
 * Data table row for procedural map generation
 * ================================
 */
USTRUCT(BlueprintType)
struct SOARFANTASY_API FMapDataRow : public FTableRowBase
{
    GENERATED_BODY()

    // プラットフォームのデータ
    // 例: "11" は 1 番プラットフォームかつ 高さ1.1倍
    // 空文字列の場合、プラットフォームは生成しない（ただし障害物は生成される可能性あり）
    // Platform data, e.g., "11" means type 1 platform with height 1.1× base
    // Empty means no platform (but obstacles may still spawn)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Data")
    FString Platform_Layer;

    // 敵のデータ
    // Enemy data
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Data")
    FString Enemy_Layer;

    // コインのデータ
    // 例: "15" は 1 番コイン × 5個
    // 空文字列の場合、コインは生成しない
    // Coin data, e.g., "15" means type 1 coin × 5 coins
    // Empty means no coins
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Data")
    FString Coin_Layer;

    // 空中障害物のデータ
    // 例: "1" は 1 番空中障害物を生成
    // 位置はプラットフォームの高さ（あれば）または基準高さ+1000単位
    // Air obstacle data, e.g., "1" means spawn type 1 aerial obstacle
    // Position is based on platform height (if exists) or base height + 1000 units
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Data")
    FString Air_Layer;
};
