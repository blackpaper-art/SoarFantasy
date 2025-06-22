// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/CoinBASE.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Characters/Kix/CharactersKix.h"

// ================================
// ACoinBASE
// ������Β��ӌgװ
// Implementation for coin behavior
// ================================

// ���󥹥ȥ饯��������ݩ`�ͥ�ȳ��ڻ�
// Constructor: initialize components
ACoinBASE::ACoinBASE()
{
    PrimaryActorTick.bCanEverTick = true;

    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    RootComponent = StaticMeshComp;

    // ���`�Щ`��åץ��٥�Ȥ�Х����
    // Bind overlap event
    StaticMeshComp->OnComponentBeginOverlap.AddDynamic(this, &ACoinBASE::OverlapBegin);
}

// ���`���_ʼ�r�γ��ڻ�
// Initialization when the game starts
void ACoinBASE::BeginPlay()
{
    Super::BeginPlay();

    // ���������ʤ��a��
    // Adjust coin score by rate
    CoinScore = CoinSocreRate * CoinScore;
}

// ���ե�`����Ф��
// Called every frame: handle magnet effect
void ACoinBASE::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bMagnetActive)
    {
        FVector NewLocation = FMath::VInterpConstantTo(GetActorLocation(), MagnetCoinTargetLocation, DeltaTime, MagnetCoinSpeed);
        SetActorLocation(NewLocation);
    }
}

// ���`�Щ`��åׄI��������׷�Ӥ��Ɨ�
// Overlap handling: add score and destroy coin
void ACoinBASE::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this)
    {
        ACharactersKix* KixCharacter = Cast<ACharactersKix>(OtherActor);
        if (KixCharacter)
        {
            KixCharacter->AddCoinScore(CoinScore);
            UGameplayStatics::PlaySound2D(GetWorld(), CoinCollectionSound);
            Destroy();
        }
    }
}

// �������Є���
// Activate magnet attraction
void ACoinBASE::ActivateMagnet(const FVector& TargetLocation)
{
    bMagnetActive = true;
    MagnetCoinTargetLocation = TargetLocation;
}

// ������o����
// Deactivate magnet attraction
void ACoinBASE::DeactivateMagnet()
{
    bMagnetActive = false;
}
