// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/GroundBASE.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ChildActorComponent.h"
#include "Items/CoinBASE.h"

// ================================
// AGroundBASE
// �ץ�åȥե��`��γ����O��
// Platform setup and spawn logic
// ================================

AGroundBASE::AGroundBASE()
{
    PrimaryActorTick.bCanEverTick = true;

    // ����ݩ`�ͥ�ȳ��ڻ�
    // Initialize components
    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    BoxCollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));

    // Box �� Root ���O��
    // Set Box as Root
    RootComponent = BoxCollisionComp;
    StaticMeshComp->SetupAttachment(BoxCollisionComp);
}

// ���`���_ʼ�r�˺��Ф��
// Called when the game starts
void AGroundBASE::BeginPlay()
{
    Super::BeginPlay();

    // �Ƅ��ٶȤ�Ӌ��
    // Calculate move speed
    PlatformCurrentSpeed = PlatformMoveSpeedBase * PlatformMoveSpeedRate;

    // ����������
    // Spawn coins
    if (CoinClass)
    {
        const float TotalWidth = CoinCount * CoinSpacing;
        const float StartY = -TotalWidth / 2 + CoinSpacing / 2;

        for (int32 i = 0; i < CoinCount; ++i)
        {
            FString Name = FString::Printf(TEXT("CoinChildComp_%d"), i);
            UChildActorComponent* CoinComp = NewObject<UChildActorComponent>(this, FName(*Name));
            if (CoinComp)
            {
                CoinComp->SetupAttachment(RootComponent);
                CoinComp->RegisterComponent();
                CoinComp->SetChildActorClass(CoinClass);

                // ����������Ϥϸߤ����٤��Ϥ���
                // If enemy exists, adjust coin Z slightly higher
                if (EnemyTypeNum > 0)
                {
                    CoinComp->SetRelativeLocation(FVector(StartY + i * CoinSpacing + 20.f, 0.f, 400.f));
                }
                else
                {
                    CoinComp->SetRelativeLocation(FVector(StartY + i * CoinSpacing + 20.f, 0.f, 300.f));
                }
                CoinComponents.Add(CoinComp);
            }
        }
    }

    // ������
    // Spawn enemy if type specified
    if (EnemyTypeNum > 0)
    {
        FString Name = FString::Printf(TEXT("EnemyComponent_%d"), EnemyTypeNum);
        UChildActorComponent* EnemyComp = NewObject<UChildActorComponent>(this, FName(*Name));
        if (EnemyComp)
        {
            EnemyComp->SetupAttachment(RootComponent);
            EnemyComp->RegisterComponent();

            switch (EnemyTypeNum)
            {
            case 1:
                if (EnemySphereClass)
                    EnemyComp->SetChildActorClass(EnemySphereClass);
                EnemyComp->SetRelativeLocation(FVector(110.f, 0.f, 150.f));
                break;
            case 2:
                if (EnemyConeClass)
                    EnemyComp->SetChildActorClass(EnemyConeClass);
                EnemyComp->SetRelativeLocation(FVector(110.f, 0.f, 200.f));
                break;
            default:
                break;
            }

            EnemyComponents.Add(EnemyComp);
        }
    }
}

// ���ե�`����ƄӄI��
// Move the platform every frame
void AGroundBASE::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AddActorLocalOffset(FVector(PlatformCurrentSpeed * DeltaTime, 0.f, 0.f));
}
