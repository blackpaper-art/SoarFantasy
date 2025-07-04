// Fill out your copyright notice in the Description page of Project Settings.

#include "SystemItems/SysSaveGame.h"
#include "Kismet/GameplayStatics.h"

// ベストスコアを隠贋する
// Save best score if current is higher
void USysSaveGame::TrySaveBestScore(int32 CurrentScore)
{
    // セ�`ブスロット兆とユ�`ザ�`インデックスを�O協
    // Define save slot name and user index
    const FString SlotName = TEXT("PlayerSaveSlot");
    const int32 UserIndex = 0;

    // スロットからロ�`ド、贋壓しなければ仟�ﾗ�撹
    // Load from slot, or create new if not found
    USysSaveGame* LoadedGame = Cast<USysSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));
    if (!LoadedGame)
    {
        LoadedGame = Cast<USysSaveGame>(UGameplayStatics::CreateSaveGameObject(USysSaveGame::StaticClass()));
    }

    if (LoadedGame)
    {
        // �F壓のスコアが�^肇のベストより互ければ厚仟
        // If current score is higher, update and save
        if (CurrentScore > LoadedGame->BestScore)
        {
            LoadedGame->BestScore = CurrentScore;
            UGameplayStatics::SaveGameToSlot(LoadedGame, SlotName, UserIndex);
        }
    }
}
