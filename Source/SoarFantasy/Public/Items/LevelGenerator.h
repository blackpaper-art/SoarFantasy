// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelGenerator.generated.h"

// ǰ������: ���Ɍ���� GroundBASE ���饹
// Forward declaration for platform class
class AGroundBASE;

/**
 * ====================================
 * ALevelGenerator
 * CSV�ե������Ԫ�˥�٥���Ԅ����ɤ��륯�饹
 * Generate level dynamically from CSV file
 * ====================================
 */
UCLASS()
class SOARFANTASY_API ALevelGenerator : public AActor
{
    GENERATED_BODY()

public:
    // ���󥹥ȥ饯��
    // Constructor
    ALevelGenerator();

    // ���Ɍ���� GroundBASE ���饹
    // Class to spawn as ground block
    UPROPERTY(EditAnywhere, Category = "Generation")
    TSubclassOf<AGroundBASE> GroundBaseClass;

    // CSV�ե�����ѥ�
    // CSV file path relative to project
    UPROPERTY(EditAnywhere, Category = "Generation")
    FString LevelFilePath = TEXT("/Source/SoarFantasy/Private/Map.csv");

    // �ޥ��g���g��
    // Spacing between grid cells
    UPROPERTY(EditAnywhere, Category = "Generation")
    float GridSpace = 200.f;

protected:
    // ���`���_ʼ�r
    // Called when the game starts
    virtual void BeginPlay() override;

private:
    // CSV�����٥�����
    // Generate level from CSV
    void GenerateLevelFromFile();

    // CSV��ѩ`�����ƶ���Ԫ���Ф�
    // Parse CSV to 2D array
    TArray<TArray<FString>> ParseCSV(const FString& FilePath);
};
