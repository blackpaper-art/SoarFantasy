// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapSpawnerBASE.generated.h"

UCLASS()
class SOARFANTASY_API AMapSpawnerBASE : public AActor
{
	GENERATED_BODY()
	
public:
    AMapSpawnerBASE();

protected:
    virtual void BeginPlay() override;

    // 数据表指针，用于读取地图数据（将在编辑器中绑定对应的DataTable资产）
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map")
    UDataTable* MapDataTable;

    // 用于生成平台、障碍物的 GroundBASE 蓝图（BP_Ground）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
    TSubclassOf<class AGroundBASE> GroundBP;

    // 地图生成的基准位置（建议设置为生成器 Actor 的位置）
    UPROPERTY(EditAnywhere, Category = "Map")
    FVector BaseLocation;

    // 平台尺寸（长,宽,高），应为 (500, 200, 500)
    UPROPERTY(EditAnywhere, Category = "Map")
    FVector PlatformSize = FVector(200.f, 500.f, 500.f);

    // 当平台数据为空时，保留的横向间隔宽度（默认200）
    UPROPERTY(EditAnywhere, Category = "Map")
    float GapWidth = 200.f;

    // 根据 DataTable 生成地图
    void GenerateMap();

public:
    virtual void Tick(float DeltaTime) override;

};
