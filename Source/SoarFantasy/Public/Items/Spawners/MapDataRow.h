// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MapDataRow.generated.h"

USTRUCT(BlueprintType)
struct SOARFANTASY_API FMapDataRow : public FTableRowBase
{
    GENERATED_BODY()

    // 平台数据，比如 "11" 表示1号样式平台且高度为基础高度的1.1倍；
    // 留空则表示此地图单元不生成平台（但后续障碍物依然可能生成）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Data")
    FString Platform_Layer;

    //Enemy Layer
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Data")
    FString Enemy_Layer;

    // 金币数据，比如 "15" 表示使用1号金币样式生成5个金币；
    // 留空则表示该平台上不生成金币
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Data")
    FString Coin_Layer;

    // 空中障碍物数据，比如 "1" 表示生成1号类型的障碍物，
    // 生成位置基于平台高度（若平台存在）或基础高度加 1000单位
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Data")
    FString Air_Layer;
};
