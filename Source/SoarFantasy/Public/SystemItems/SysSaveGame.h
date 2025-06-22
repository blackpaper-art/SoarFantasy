// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SysSaveGame.generated.h"

/**
 * ================================
 * USysSaveGame
 * �٥��ȥ����������äΥ��`�֥ǩ`�����饹
 * SaveGame class for storing best score
 * ================================
 */
UCLASS()
class SOARFANTASY_API USysSaveGame : public USaveGame
{
    GENERATED_BODY()

public:
    // �٥��ȥ������򥻩`�֤��뾲���v��
    // Static function to save best score if higher
    UFUNCTION(BlueprintCallable, Category = "SaveGame")
    static void TrySaveBestScore(int32 CurrentScore);

    // �٥��ȥ�������
    // Best score value
    UPROPERTY(VisibleAnywhere, Category = "SaveGame")
    int32 BestScore = 0;
};
