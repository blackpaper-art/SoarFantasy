// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SysSaveGame.generated.h"

/**
 * ================================
 * USysSaveGame
 * ベストスコア保存用のセーブデータクラス
 * SaveGame class for storing best score
 * ================================
 */
UCLASS()
class SOARFANTASY_API USysSaveGame : public USaveGame
{
    GENERATED_BODY()

public:
    // ベストスコアをセーブする静的関数
    // Static function to save best score if higher
    UFUNCTION(BlueprintCallable, Category = "SaveGame")
    static void TrySaveBestScore(int32 CurrentScore);

    // ベストスコア値
    // Best score value
    UPROPERTY(VisibleAnywhere, Category = "SaveGame")
    int32 BestScore = 0;
};
