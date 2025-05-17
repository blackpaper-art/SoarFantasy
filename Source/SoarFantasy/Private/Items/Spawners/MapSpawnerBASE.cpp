// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Spawners/MapSpawnerBASE.h"
#include "Items/GroundBASE.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Items/Spawners/MapDataRow.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMapSpawnerBASE::AMapSpawnerBASE()
{
	PrimaryActorTick.bCanEverTick = false;
	BaseLocation = GetActorLocation();
}

// Called when the game starts or when spawned
void AMapSpawnerBASE::BeginPlay()
{
	Super::BeginPlay();
	GenerateMap();
}

// Called every frame
void AMapSpawnerBASE::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMapSpawnerBASE::GenerateMap()
{
    if (!MapDataTable)
    {
        UE_LOG(LogTemp, Error, TEXT("MapDataTable is not assigned."));
        return;
    }

    // ��ȡ���ݱ��������е�����
    static const FString ContextString(TEXT("MapData"));
    TArray<FMapDataRow*> AllRows;
    MapDataTable->GetAllRows<FMapDataRow>(ContextString, AllRows);

    // ��ʼ����λ�ã�X���꣩���� BaseLocation.X ��ʼ
    float CurrentX = BaseLocation.X;
    // �̶��� Y ���꣨���ٸı䣩
    float FixedY = BaseLocation.Y;

    for (FMapDataRow* Row : AllRows)
    {
        if (!Row)
        {
            continue;
        }

        // ��ȡ�������ݣ���ȥ����β�ո�
        FString PlatformStr = Row->Platform_Layer.TrimStartAndEnd();
        FString EnemyStr = Row->Enemy_Layer.TrimStartAndEnd();
        FString CoinStr = Row->Coin_Layer.TrimStartAndEnd();
        FString AirStr = Row->Air_Layer.TrimStartAndEnd();

        // ��������λ�ã�X Ϊ��ǰ�ۻ�λ��, Y ʹ�ù̶�ֵ, Z ����ƽ̨���ݾ���
        float SpawnX = CurrentX;
        float SpawnY = FixedY;
        float BaseZ = BaseLocation.Z;
        float PlatformZ = BaseZ;

        AGroundBASE* PlatformActor = nullptr;
        if (!PlatformStr.IsEmpty())
        {
            // �� Platform_Layer �ַ���ת��Ϊ���������� "11" תΪ 11��
            int32 PlatformValue = FCString::Atoi(*PlatformStr);
            // ʮλ����ƽ̨��ʽ����λ����߶ȵȼ���0 ��ʾ1.0����1 ��ʾ1.1��������
            int32 ParsedPlatformStyle = PlatformValue / 10;
            int32 HeightLevel = PlatformValue % 10;
            float HeightMultiplier = 1.f + HeightLevel * 0.1f;
            PlatformZ = BaseZ * HeightMultiplier;
            FVector SpawnLocation(SpawnX, SpawnY, PlatformZ);
            FRotator SpawnRotation = FRotator::ZeroRotator;
            FTransform SpawnTransform(SpawnRotation, SpawnLocation);

            // ʹ���ӳ����ɣ��� FinishSpawningActor ǰ���ø�������
            PlatformActor = GetWorld()->SpawnActorDeferred<AGroundBASE>(GroundBP, SpawnTransform);
            if (PlatformActor)
            {
                // ����ƽ̨��ʽ
                PlatformActor->PlatformStyle = ParsedPlatformStyle;

                // ���������ݲ�Ϊ�գ������ý������
                if (!CoinStr.IsEmpty())
                {
                    int32 CoinValue = FCString::Atoi(*CoinStr);
                    // ʮλ��ʾ�����ʽ����λ��ʾ���ɽ������������ "15" ��ʾ1����ʽ����5����ң�
                    int32 ParsedCoinStyle = CoinValue / 10;
                    int32 ParsedCoinCount = CoinValue % 10;
                    PlatformActor->CoinStyle = ParsedCoinStyle;
                    PlatformActor->CoinCount = ParsedCoinCount;
                }

                // Enemy
                if (!EnemyStr.IsEmpty())
                {
                    int32 EnemyValue = FCString::Atoi(*EnemyStr);
                    if (EnemyValue != 0 && PlatformActor)
                    {
                        // ���õ����ࣨ���������� MapSpawner ����ͼ�����ã�
                        PlatformActor->EnemyTypeNum = EnemyValue;
                    }
                }

                // ������ɣ�BeginPlay ����֮����ã���ʱ���������������ú�
                UGameplayStatics::FinishSpawningActor(PlatformActor, SpawnTransform);
            }
        }

        // ��������ϰ��ֻҪ Air_Layer ��Ϊ�վ�����
        if (!AirStr.IsEmpty())
        {
            int32 ObstacleStyle = FCString::Atoi(*AirStr);
            // �ϰ�������λ�ã�X �� Y ͬ�ϣ�Z Ϊ��ƽ̨�߶Ȼ�����߶ȣ�+ 1000
            float ObstacleZ = (PlatformActor ? PlatformZ : BaseZ) + 1000.f;
            FVector ObstacleLocation(SpawnX, SpawnY, ObstacleZ);
            FRotator ObstacleRotation = FRotator::ZeroRotator;
            AGroundBASE* ObstacleActor = GetWorld()->SpawnActor<AGroundBASE>(GroundBP, ObstacleLocation, ObstacleRotation);
            if (ObstacleActor)
            {
                ObstacleActor->ObstacleStyle = ObstacleStyle;
                // �ϰ���һ�㲻�󶨽�ң����� Blueprint �и��� ObstacleStyle �����ִ���
            }
        }

        // ÿһ�������� X ��ռ�ù̶���ȣ�
        // ���ƽ̨������ʹ��ƽ̨�� X �ߴ磬����ճ� GapWidth ��λ�ļ��
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