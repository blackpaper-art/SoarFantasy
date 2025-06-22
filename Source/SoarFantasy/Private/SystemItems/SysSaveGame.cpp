// Fill out your copyright notice in the Description page of Project Settings.

#include "SystemItems/SysSaveGame.h"
#include "Kismet/GameplayStatics.h"

// ベストスコアを保存する
// Save best score if current is higher
void USysSaveGame::TrySaveBestScore(int32 CurrentScore)
{
    // セーブスロット名とユーザーインデックスを設定
    // Define save slot name and user index
    const FString SlotName = TEXT("PlayerSaveSlot");
    const int32 UserIndex = 0;

    // スロットからロード、存在しなければ新規作成
    // Load from slot, or create new if not found
    USysSaveGame* LoadedGame = Cast<USysSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));
    if (!LoadedGame)
    {
        LoadedGame = Cast<USysSaveGame>(UGameplayStatics::CreateSaveGameObject(USysSaveGame::StaticClass()));
    }

    if (LoadedGame)
    {
        // 現在のスコアが過去のベストより高ければ更新
        // If current score is higher, update and save
        if (CurrentScore > LoadedGame->BestScore)
        {
            LoadedGame->BestScore = CurrentScore;
            UGameplayStatics::SaveGameToSlot(LoadedGame, SlotName, UserIndex);
        }
    }
}
