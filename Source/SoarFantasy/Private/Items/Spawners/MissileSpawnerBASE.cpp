// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/Spawners/MissileSpawnerBASE.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"

// ================================
// AMissileSpawnerBASE
// �ߥ����룦�Хդ����ɹ����饹
// Class for managing missile and buff spawning
// ================================

// ���󥹥ȥ饯��
// Constructor
AMissileSpawnerBASE::AMissileSpawnerBASE()
{
    // Tick ��ʹ�ä��ʤ�
    // Tick is not needed
    PrimaryActorTick.bCanEverTick = false;
}

// ���`���_ʼ�r�˥����ީ`���O��
// Set up timers when the game starts
void AMissileSpawnerBASE::BeginPlay()
{
    Super::BeginPlay();

    // �ߥ��������ɤ��g���������˛Q��
    // Randomize missile spawn interval
    RandomTimerCount = FMath::RandRange(MinTimerCount, MaxTimerCount);

    // �ߥ��������ɥ����ީ`������
    // Start missile spawn timer
    GetWorldTimerManager().SetTimer(
        MissileSpawnTimerHandle,
        this,
        &AMissileSpawnerBASE::SpawnMissile,
        RandomTimerCount,
        true
    );

    // �Х����ɥ����ީ`�����ӣ��̶�30���g����
    // Start buff spawn timer (fixed 30 seconds)
    GetWorldTimerManager().SetTimer(
        BuffSpawnTimerHandle,
        this,
        &AMissileSpawnerBASE::SpawnBuff,
        30,
        true
    );
}

// �ߥ���������ɤ���
// Spawn a missile actor
void AMissileSpawnerBASE::SpawnMissile()
{
    // �ץ쥤��`��ȡ��
    // Get player pawn
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (!PlayerPawn)
    {
        return;
    }

    // ����λ�ä�Ӌ�㣨�ץ쥤��`Z + 200��
    // Calculate spawn location (player Z + 200)
    FVector MyLocation = GetActorLocation();
    float PlayerZ = PlayerPawn->GetActorLocation().Z + 200.f;

    // �ץ쥤��`�������
    // Rotate to face player direction
    FRotator PlayerRotator = FRotator(0, 180, 0);

    FVector SpawnLocation = FVector(MyLocation.X, MyLocation.Y, PlayerZ);

    // �ߥ����������
    // Spawn missile actor
    GetWorld()->SpawnActor<AActor>(BPMissile, SpawnLocation, PlayerRotator);
}

// �Хդ����ɤ���
// Spawn a buff actor
void AMissileSpawnerBASE::SpawnBuff()
{
    // �ץ쥤��`��ȡ��
    // Get player pawn
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (!PlayerPawn)
    {
        return;
    }

    // ����λ�ä�Ӌ�㣨�ץ쥤��`Z��
    // Calculate spawn location (player Z)
    FVector MyLocation = GetActorLocation();
    float PlayerZ = PlayerPawn->GetActorLocation().Z;

    // �ץ쥤��`�������
    // Rotate to face player direction
    FRotator PlayerRotator = FRotator(0, 180, 0);

    FVector SpawnLocation = FVector(MyLocation.X, MyLocation.Y, PlayerZ);

    // �Хդ�����
    // Spawn buff actor
    GetWorld()->SpawnActor<AActor>(BPMagnet, SpawnLocation, PlayerRotator);
}
