// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelGenerator.generated.h"

class AGroundBASE;

UCLASS()
class SOARFANTASY_API ALevelGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	ALevelGenerator();

	UPROPERTY(EditAnywhere, Category = "Generation")
	TSubclassOf<AGroundBASE> GroundBaseClass;

	UPROPERTY(EditAnywhere, Category = "Generation")
	FString LevelFilePath = TEXT("/Source/SoarFantasy/Private/Map.csv");

	UPROPERTY(EditAnywhere, Category = "Generation")
	float GridSpace = 200.f;

protected:
	virtual void BeginPlay() override;

private:
	void GenerateLevelFromFile();
	TArray<TArray<FString>> ParseCSV(const FString& FilePath);
};
