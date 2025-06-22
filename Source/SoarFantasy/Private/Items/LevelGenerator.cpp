// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/LevelGenerator.h"
#include "Items/GroundBASE.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Engine/World.h"

// ====================================
// コンストラクタ: Tickを無効化
// Constructor: disable tick
// ====================================
ALevelGenerator::ALevelGenerator()
{
    PrimaryActorTick.bCanEverTick = false;
}

// ====================================
// BeginPlay: CSVからレベル生成を呼ぶ
// Called when the game starts: generate level from CSV
// ====================================
void ALevelGenerator::BeginPlay()
{
    Super::BeginPlay();

    GenerateLevelFromFile();
}

// ====================================
// CSVからレベルを生成
// Generate level blocks based on CSV data
// ====================================
void ALevelGenerator::GenerateLevelFromFile()
{
    TArray<TArray<FString>> CSVData = ParseCSV(LevelFilePath);

    for (int32 Row = 0; Row < CSVData.Num(); ++Row)
    {
        for (int32 Col = 0; Col < CSVData[Row].Num(); ++Col)
        {
            FString Cell = CSVData[Row][Col];

            if (Cell == TEXT("11"))
            {
                FVector SpawnLocation = GetActorLocation() + FVector(0, Col * GridSpace, Row * GridSpace);
                GetWorld()->SpawnActor<AGroundBASE>(GroundBaseClass, SpawnLocation, FRotator::ZeroRotator);
            }
        }
    }
}

// ====================================
// CSVを二次元配列にパース
// Parse CSV file to 2D array of strings
// ====================================
TArray<TArray<FString>> ALevelGenerator::ParseCSV(const FString& FilePath)
{
    TArray<TArray<FString>> ParsedCSV;
    FString AbsolutePath = FPaths::ProjectDir() + FilePath;
    FString FileData;

    if (FFileHelper::LoadFileToString(FileData, *AbsolutePath))
    {
        TArray<FString> Rows;
        FileData.ParseIntoArrayLines(Rows);

        for (const FString& Row : Rows)
        {
            TArray<FString> Cells;
            Row.ParseIntoArray(Cells, TEXT(","), true);
            ParsedCSV.Add(Cells);
        }
    }

    return ParsedCSV;
}
