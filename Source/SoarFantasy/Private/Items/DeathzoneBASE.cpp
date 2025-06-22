#include "Items/DeathzoneBASE.h"
#include "Components/BoxComponent.h"

// ====================================
// コンストラクタ: BoxComponent を初期化
// Constructor: Initialize BoxComponent
// ====================================
ADeathzoneBASE::ADeathzoneBASE()
{
    PrimaryActorTick.bCanEverTick = false;

    BoxCollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollisionComp"));
    RootComponent = BoxCollisionComp;

    // Box サイズを設定
    BoxCollisionComp->SetBoxExtent(FVector(250.f, 250.f, 50.f));
}

// ====================================
// BeginPlay(): 現状では追加処理なし
// Called when the game starts (currently empty)
// ====================================
void ADeathzoneBASE::BeginPlay()
{
    Super::BeginPlay();
}
