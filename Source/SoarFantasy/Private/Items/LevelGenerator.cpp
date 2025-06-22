// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/LevelGenerator.h"
#include "Items/GroundBASE.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Engine/World.h"

// ====================================
// ���󥹥ȥ饯��: Tick��o����
// Constructor: disable tick
// ====================================
ALevelGenerator::ALevelGenerator()
{
    PrimaryActorTick.bCanEverTick = false;
}

// ====================================
// BeginPlay: CSV�����٥����ɤ����
// Called when the game starts: generate level from CSV
// ====================================
void ALevelGenerator::BeginPlay()
{
    Super::BeginPlay();

    GenerateLevelFromFile();
}

// ====================================
// CSV�����٥������
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
// CSV�����Ԫ���Ф˥ѩ`��
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
