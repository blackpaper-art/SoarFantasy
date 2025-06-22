// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/CoinBASE.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Characters/Kix/CharactersKix.h"

// ================================
// ACoinBASE
// コインの挙動実装
// Implementation for coin behavior
// ================================

// コンストラクタ：コンポーネント初期化
// Constructor: initialize components
ACoinBASE::ACoinBASE()
{
    PrimaryActorTick.bCanEverTick = true;

    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    RootComponent = StaticMeshComp;

    // オーバーラップイベントをバインド
    // Bind overlap event
    StaticMeshComp->OnComponentBeginOverlap.AddDynamic(this, &ACoinBASE::OverlapBegin);
}

// ゲーム開始時の初期化
// Initialization when the game starts
void ACoinBASE::BeginPlay()
{
    Super::BeginPlay();

    // スコアを倍率で補正
    // Adjust coin score by rate
    CoinScore = CoinSocreRate * CoinScore;
}

// 毎フレーム呼ばれる
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

// オーバーラップ処理：スコア追加と破棄
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

// 磁力を有効化
// Activate magnet attraction
void ACoinBASE::ActivateMagnet(const FVector& TargetLocation)
{
    bMagnetActive = true;
    MagnetCoinTargetLocation = TargetLocation;
}

// 磁力を無効化
// Deactivate magnet attraction
void ACoinBASE::DeactivateMagnet()
{
    bMagnetActive = false;
}
