// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SoarFantasyInterface.generated.h"

/**
 * ====================================
 * USoarFantasyInterface
 * SoarFantasy用の共通インターフェース
 * Common interface for SoarFantasy objects
 * ====================================
 */
UINTERFACE(MinimalAPI)
class USoarFantasyInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * ====================================
 * ISoarFantasyInterface
 * このインターフェースを継承するクラスが実装する機能
 * Functions that inheriting classes should implement
 * ====================================
 */
class SOARFANTASY_API ISoarFantasyInterface
{
    GENERATED_BODY()

public:
    // コインスコアを加算する共通関数
    // Add coin score function (to be overridden)
    virtual void AddCoinScore(int32 Score);
};
