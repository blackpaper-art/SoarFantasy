// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SysSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class SOARFANTASY_API USysSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	static void TrySaveBestScore(int32 CurrentScore);
	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	int32 BestScore = 0;
};
