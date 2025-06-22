// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MissileSpawnerBASE.generated.h"

/**
 * ====================================
 * AMissileSpawnerBASE
 * �ߥ����� & �Хդ������ɤ��륹�ѥ���
 * Spawner that periodically spawns missiles and buffs
 * ====================================
 */
UCLASS()
class SOARFANTASY_API AMissileSpawnerBASE : public AActor
{
    GENERATED_BODY()

public:
    // ���󥹥ȥ饯��
    // Constructor
    AMissileSpawnerBASE();

protected:
    // ���`���_ʼ�r�˺��Ф��
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // �ߥ����������å����ީ`�ϥ�ɥ�
    // Timer handle for missile spawning
    FTimerHandle MissileSpawnTimerHandle;

    // �Х������å����ީ`�ϥ�ɥ�
    // Timer handle for buff spawning
    FTimerHandle BuffSpawnTimerHandle;

    // �ߥ��������ɤ���̕r�g
    // Minimum spawn interval for missiles
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn")
    float MinTimerCount = 3.f;

    // �ߥ��������ɤ����L�r�g
    // Maximum spawn interval for missiles
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn")
    float MaxTimerCount = 15.f;

    // ���ɤ���ߥ������BP���饹
    // BP class of missile to spawn
    UPROPERTY(EditAnywhere, Category = "Spawn")
    TSubclassOf<AActor> BPMissile;

    // ���ɤ���Хդ�BP���饹
    // BP class of buff to spawn
    UPROPERTY(EditAnywhere, Category = "Spawn")
    TSubclassOf<AActor> BPMagnet;

private:
    // ������˛Q������������g��
    // Random spawn interval
    float RandomTimerCount;

    // �ߥ����������
    // Spawn a missile
    void SpawnMissile();

    // �Хդ�����
    // Spawn a buff
    void SpawnBuff();
};
