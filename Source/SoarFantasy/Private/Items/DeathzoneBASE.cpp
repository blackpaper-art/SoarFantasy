#include "Items/DeathzoneBASE.h"
#include "Components/BoxComponent.h"

// ====================================
// コンストラクタ: BoxComponent を兜豚晒
// Constructor: Initialize BoxComponent
// ====================================
ADeathzoneBASE::ADeathzoneBASE()
{
    PrimaryActorTick.bCanEverTick = false;

    BoxCollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollisionComp"));
    RootComponent = BoxCollisionComp;

    // Box サイズを�O協
    BoxCollisionComp->SetBoxExtent(FVector(250.f, 250.f, 50.f));
}

// ====================================
// BeginPlay(): �F彜では弖紗�I尖なし
// Called when the game starts (currently empty)
// ====================================
void ADeathzoneBASE::BeginPlay()
{
    Super::BeginPlay();
}
