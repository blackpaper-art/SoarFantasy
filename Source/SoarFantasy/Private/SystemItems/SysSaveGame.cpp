// Fill out your copyright notice in the Description page of Project Settings.

#include "SystemItems/SysSaveGame.h"
#include "Kismet/GameplayStatics.h"

// �٥��ȥ������򱣴椹��
// Save best score if current is higher
void USysSaveGame::TrySaveBestScore(int32 CurrentScore)
{
    // ���`�֥���å����ȥ�`���`����ǥå������O��
    // Define save slot name and user index
    const FString SlotName = TEXT("PlayerSaveSlot");
    const int32 UserIndex = 0;

    // ����åȤ����`�ɡ����ڤ��ʤ������Ҏ����
    // Load from slot, or create new if not found
    USysSaveGame* LoadedGame = Cast<USysSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));
    if (!LoadedGame)
    {
        LoadedGame = Cast<USysSaveGame>(UGameplayStatics::CreateSaveGameObject(USysSaveGame::StaticClass()));
    }

    if (LoadedGame)
    {
        // �F�ڤΥ��������^ȥ�Υ٥��Ȥ��ߤ���и���
        // If current score is higher, update and save
        if (CurrentScore > LoadedGame->BestScore)
        {
            LoadedGame->BestScore = CurrentScore;
            UGameplayStatics::SaveGameToSlot(LoadedGame, SlotName, UserIndex);
        }
    }
}
