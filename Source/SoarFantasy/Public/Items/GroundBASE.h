// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GroundBASE.generated.h"

/**
 * ====================================
 * AGroundBASE
 * �ץ�åȥե��`��λ����������`
 * Base actor for moving platforms with coins and enemies
 * ====================================
 */
UCLASS()
class SOARFANTASY_API AGroundBASE : public AActor
{
    GENERATED_BODY()

public:
    // ���󥹥ȥ饯��
    // Constructor
    AGroundBASE();

    // ���ե�`��θ���
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // �ץ�åȥե��`���Ҋ��Ŀ
    // Visual mesh for the platform
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
    class UStaticMeshComponent* StaticMeshComp;

    // �nͻ�ж��åܥå���
    // Collision box component
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
    class UBoxComponent* BoxCollisionComp;

    // �Ƅ��ٶȱ���
    // Platform move speed multiplier
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float PlatformMoveSpeedRate = 1.f;

    // ����� Y λ��
    // Ground position Y
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location", meta = (ExposeOnSpawn = "true"))
    float GroundPostionY;

    // ���ݩ`��λ��
    // Spawn location
    FVector SpawnLocation;

    // �g�H�ε���λ��
    // Actual ground location
    FVector GroundLocation;

    // �����������å��饹
    // Coin actor class
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
    TSubclassOf<AActor> CoinClass;

    // ���������
    // Number of coins
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin", meta = (ExposeOnSpawn = "true"))
    int32 CoinCount = 5;

    // ��������g��
    // Spacing between coins
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
    float CoinSpacing = 80.f;

    // �����󥳥�ݩ`�ͥ������
    // Array of coin child components
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
    TArray<UChildActorComponent*> CoinComponents;

    // �ץ�åȥե��`��Υ�������
    // Platform style ID
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style")
    int32 PlatformStyle = 0;

    // ������Υ�������
    // Coin style ID
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
    int32 CoinStyle = 0;

    // �Ϻ���Υ�������
    // Obstacle style ID
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle")
    int32 ObstacleStyle = 0;

    // �������壩�Υ��饹
    // Enemy sphere class
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
    TSubclassOf<AActor> EnemySphereClass;

    // �������`���ͣ��Υ��饹
    // Enemy cone class
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
    TSubclassOf<AActor> EnemyConeClass;

    // �������׷���
    // Enemy type number
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy", meta = (ExposeOnSpawn = "true"))
    int32 EnemyTypeNum = 0;

    // ������ݩ`�ͥ������
    // Array of enemy child components
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
    TArray<UChildActorComponent*> EnemyComponents;

protected:
    // ���`���_ʼ�r�γ��ڻ�
    // Called when the game starts
    virtual void BeginPlay() override;

private:
    // �����Ƅ��ٶ�
    // Base move speed
    float PlatformMoveSpeedBase = -600.f;

    // �F�ڤ��Ƅ��ٶ�
    // Current move speed
    float PlatformCurrentSpeed;
};
