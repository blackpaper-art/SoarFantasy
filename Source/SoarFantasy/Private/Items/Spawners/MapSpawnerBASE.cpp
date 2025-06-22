// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/Spawners/MapSpawnerBASE.h"
#include "Items/GroundBASE.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Items/Spawners/MapDataRow.h"
#include "Kismet/GameplayStatics.h"

// ================================
// AMapSpawnerBASE
// �ޥå����ɤλ��ץ��饹
// Base class for procedural map generation
// ================================

// ���󥹥ȥ饯��������λ�ä򱣴�
// Constructor: save base location
AMapSpawnerBASE::AMapSpawnerBASE()
{
    PrimaryActorTick.bCanEverTick = false;
    BaseLocation = GetActorLocation();
}

// ���`���_ʼ�r�˥ޥå����ɤ���ӳ���
// Call map generation when the game starts
void AMapSpawnerBASE::BeginPlay()
{
    Super::BeginPlay();
    GenerateMap();
}

// Tick ��δʹ��
// Tick not used
void AMapSpawnerBASE::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// �ޥå����ɥᥤ��I��
// Main logic for generating the map
void AMapSpawnerBASE::GenerateMap()
{
    if (!MapDataTable)
    {
        UE_LOG(LogTemp, Error, TEXT("MapDataTable is not assigned."));
        return;
    }

    // �ǩ`���Ʃ`�֥뤫��ȫ��ȡ��
    // Get all rows from data table
    static const FString ContextString(TEXT("MapData"));
    TArray<FMapDataRow*> AllRows;
    MapDataTable->GetAllRows<FMapDataRow>(ContextString, AllRows);

    // X�S���ڂ����᷽����_ʼλ�ã�
    // Initial X position
    float CurrentX = BaseLocation.X;

    // Y�S�Ϲ̶���
    // Y position is fixed
    float FixedY = BaseLocation.Y;

    for (FMapDataRow* Row : AllRows)
    {
        if (!Row)
        {
            continue;
        }

        // ���쥤��`�����Ф�ȡ�� & �ȥ��
        // Get and trim each layer string
        FString PlatformStr = Row->Platform_Layer.TrimStartAndEnd();
        FString EnemyStr = Row->Enemy_Layer.TrimStartAndEnd();
        FString CoinStr = Row->Coin_Layer.TrimStartAndEnd();
        FString AirStr = Row->Air_Layer.TrimStartAndEnd();

        // �������ˤ�Ӌ�㣺X���۷e����Y�Ϲ̶���Z�ϥץ�åȥե��`��θߤ�
        // Calculate spawn position: X = current, Y = fixed, Z = platform height
        float SpawnX = CurrentX;
        float SpawnY = FixedY;
        float BaseZ = BaseLocation.Z;
        float PlatformZ = BaseZ;

        AGroundBASE* PlatformActor = nullptr;

        // �ץ�åȥե��`�����ɄI��
        // Platform generation
        if (!PlatformStr.IsEmpty())
        {
            int32 PlatformValue = FCString::Atoi(*PlatformStr);
            int32 ParsedPlatformStyle = PlatformValue / 10;
            int32 HeightLevel = PlatformValue % 10;
            float HeightMultiplier = 1.f + HeightLevel * 0.1f;
            PlatformZ = BaseZ * HeightMultiplier;

            FVector SpawnLocation(SpawnX, SpawnY, PlatformZ);
            FRotator SpawnRotation = FRotator::ZeroRotator;
            FTransform SpawnTransform(SpawnRotation, SpawnLocation);

            // �ǥ��ե��`�����ɤǸ��ץ�ѥƥ��O��
            // Deferred spawn to set properties before BeginPlay
            PlatformActor = GetWorld()->SpawnActorDeferred<AGroundBASE>(GroundBP, SpawnTransform);
            if (PlatformActor)
            {
                PlatformActor->PlatformStyle = ParsedPlatformStyle;

                // �������O��
                // Coin setup
                if (!CoinStr.IsEmpty())
                {
                    int32 CoinValue = FCString::Atoi(*CoinStr);
                    int32 ParsedCoinStyle = CoinValue / 10;
                    int32 ParsedCoinCount = CoinValue % 10;
                    PlatformActor->CoinStyle = ParsedCoinStyle;
                    PlatformActor->CoinCount = ParsedCoinCount;
                }

                // ���O��
                // Enemy setup
                if (!EnemyStr.IsEmpty())
                {
                    int32 EnemyValue = FCString::Atoi(*EnemyStr);
                    if (EnemyValue != 0 && PlatformActor)
                    {
                        PlatformActor->EnemyTypeNum = EnemyValue;
                    }
                }

                // ��������
                // Finish spawning
                UGameplayStatics::FinishSpawningActor(PlatformActor, SpawnTransform);
            }
        }

        // �����Ϻ�������
        // Aerial obstacle generation
        if (!AirStr.IsEmpty())
        {
            int32 ObstacleStyle = FCString::Atoi(*AirStr);
            float ObstacleZ = (PlatformActor ? PlatformZ : BaseZ) + 1000.f;
            FVector ObstacleLocation(SpawnX, SpawnY, ObstacleZ);
            FRotator ObstacleRotation = FRotator::ZeroRotator;

            AGroundBASE* ObstacleActor = GetWorld()->SpawnActor<AGroundBASE>(GroundBP, ObstacleLocation, ObstacleRotation);
            if (ObstacleActor)
            {
                ObstacleActor->ObstacleStyle = ObstacleStyle;
                // Blueprint �� ObstacleStyle �ˏꤸ�ƄI�����
                // Handle specifics in Blueprint using ObstacleStyle
            }
        }

        // Xλ�ä���£��ץ�åȥե��`����ޤ���GapWidth
        // Update X position: platform width or gap width
        if (!PlatformStr.IsEmpty())
        {
            CurrentX += PlatformSize.X;
        }
        else
        {
            CurrentX += GapWidth;
        }
    }
}
