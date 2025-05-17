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

    // 获取数据表中所有行的数据
    static const FString ContextString(TEXT("MapData"));
    TArray<FMapDataRow*> AllRows;
    MapDataTable->GetAllRows<FMapDataRow>(ContextString, AllRows);

    // 初始横向位置（X坐标），从 BaseLocation.X 开始
    float CurrentX = BaseLocation.X;
    // 固定的 Y 坐标（不再改变）
    float FixedY = BaseLocation.Y;

    for (FMapDataRow* Row : AllRows)
    {
        if (!Row)
        {
            continue;
        }

        // 获取各列数据，并去除首尾空格
        FString PlatformStr = Row->Platform_Layer.TrimStartAndEnd();
        FString EnemyStr = Row->Enemy_Layer.TrimStartAndEnd();
        FString CoinStr = Row->Coin_Layer.TrimStartAndEnd();
        FString AirStr = Row->Air_Layer.TrimStartAndEnd();

        // 计算生成位置：X 为当前累积位置, Y 使用固定值, Z 根据平台数据决定
        float SpawnX = CurrentX;
        float SpawnY = FixedY;
        float BaseZ = BaseLocation.Z;
        float PlatformZ = BaseZ;

        AGroundBASE* PlatformActor = nullptr;
        if (!PlatformStr.IsEmpty())
        {
            // 将 Platform_Layer 字符串转换为整数（例如 "11" 转为 11）
            int32 PlatformValue = FCString::Atoi(*PlatformStr);
            // 十位代表平台样式，个位代表高度等级（0 表示1.0倍，1 表示1.1倍……）
            int32 ParsedPlatformStyle = PlatformValue / 10;
            int32 HeightLevel = PlatformValue % 10;
            float HeightMultiplier = 1.f + HeightLevel * 0.1f;
            PlatformZ = BaseZ * HeightMultiplier;
            FVector SpawnLocation(SpawnX, SpawnY, PlatformZ);
            FRotator SpawnRotation = FRotator::ZeroRotator;
            FTransform SpawnTransform(SpawnRotation, SpawnLocation);

            // 使用延迟生成，在 FinishSpawningActor 前设置各项属性
            PlatformActor = GetWorld()->SpawnActorDeferred<AGroundBASE>(GroundBP, SpawnTransform);
            if (PlatformActor)
            {
                // 设置平台样式
                PlatformActor->PlatformStyle = ParsedPlatformStyle;

                // 如果金币数据不为空，则设置金币属性
                if (!CoinStr.IsEmpty())
                {
                    int32 CoinValue = FCString::Atoi(*CoinStr);
                    // 十位表示金币样式，个位表示生成金币数量（例如 "15" 表示1号样式生成5个金币）
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
                        // 设置敌人类（假设你已在 MapSpawner 或蓝图中配置）
                        PlatformActor->EnemyTypeNum = EnemyValue;
                    }
                }

                // 完成生成，BeginPlay 在这之后调用，此时金币相关属性已设置好
                UGameplayStatics::FinishSpawningActor(PlatformActor, SpawnTransform);
            }
        }

        // 处理空中障碍物：只要 Air_Layer 不为空就生成
        if (!AirStr.IsEmpty())
        {
            int32 ObstacleStyle = FCString::Atoi(*AirStr);
            // 障碍物生成位置：X 与 Y 同上，Z 为（平台高度或基础高度）+ 1000
            float ObstacleZ = (PlatformActor ? PlatformZ : BaseZ) + 1000.f;
            FVector ObstacleLocation(SpawnX, SpawnY, ObstacleZ);
            FRotator ObstacleRotation = FRotator::ZeroRotator;
            AGroundBASE* ObstacleActor = GetWorld()->SpawnActor<AGroundBASE>(GroundBP, ObstacleLocation, ObstacleRotation);
            if (ObstacleActor)
            {
                ObstacleActor->ObstacleStyle = ObstacleStyle;
                // 障碍物一般不绑定金币，可在 Blueprint 中根据 ObstacleStyle 做区分处理
            }
        }

        // 每一行数据沿 X 轴占用固定宽度：
        // 如果平台存在则使用平台的 X 尺寸，否则空出 GapWidth 单位的间隔
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