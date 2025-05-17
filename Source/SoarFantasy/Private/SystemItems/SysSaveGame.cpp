// Fill out your copyright notice in the Description page of Project Settings.


#include "SystemItems/SysSaveGame.h"
#include "Kismet/GameplayStatics.h"

void USysSaveGame::TrySaveBestScore(int32 CurrentScore)
{
	const FString SlotName = TEXT("PlayerSaveSlot");
	const int32 UserIndex = 0;

	USysSaveGame* LoadedGame = Cast<USysSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));
	if (!LoadedGame)
	{
		LoadedGame = Cast<USysSaveGame>(UGameplayStatics::CreateSaveGameObject(USysSaveGame::StaticClass()));
	}
	if (LoadedGame)
	{
		if (CurrentScore > LoadedGame->BestScore)
		{
			LoadedGame->BestScore = CurrentScore;
			UGameplayStatics::SaveGameToSlot(LoadedGame, SlotName, UserIndex);
		}
	}
}
