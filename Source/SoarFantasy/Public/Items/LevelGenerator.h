// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelGenerator.generated.h"

// 前方宣言: 生成対象の GroundBASE クラス
// Forward declaration for platform class
class AGroundBASE;

/**
 * ====================================
 * ALevelGenerator
 * CSVファイルを元にレベルを自動生成するクラス
 * Generate level dynamically from CSV file
 * ====================================
 */
UCLASS()
class SOARFANTASY_API ALevelGenerator : public AActor
{
    GENERATED_BODY()

public:
    // コンストラクタ
    // Constructor
    ALevelGenerator();

    // 生成対象の GroundBASE クラス
    // Class to spawn as ground block
    UPROPERTY(EditAnywhere, Category = "Generation")
    TSubclassOf<AGroundBASE> GroundBaseClass;

    // CSVファイルパス
    // CSV file path relative to project
    UPROPERTY(EditAnywhere, Category = "Generation")
    FString LevelFilePath = TEXT("/Source/SoarFantasy/Private/Map.csv");

    // マス間の間隔
    // Spacing between grid cells
    UPROPERTY(EditAnywhere, Category = "Generation")
    float GridSpace = 200.f;

protected:
    // ゲーム開始時
    // Called when the game starts
    virtual void BeginPlay() override;

private:
    // CSVからレベル生成
    // Generate level from CSV
    void GenerateLevelFromFile();

    // CSVをパースして二次元配列に
    // Parse CSV to 2D array
    TArray<TArray<FString>> ParseCSV(const FString& FilePath);
};
