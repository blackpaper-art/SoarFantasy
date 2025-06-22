#include "Items/DeathzoneBASE.h"
#include "Components/BoxComponent.h"

// ====================================
// ���󥹥ȥ饯��: BoxComponent ����ڻ�
// Constructor: Initialize BoxComponent
// ====================================
ADeathzoneBASE::ADeathzoneBASE()
{
    PrimaryActorTick.bCanEverTick = false;

    BoxCollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollisionComp"));
    RootComponent = BoxCollisionComp;

    // Box ���������O��
    BoxCollisionComp->SetBoxExtent(FVector(250.f, 250.f, 50.f));
}

// ====================================
// BeginPlay(): �F״�Ǥ�׷�ӄI��ʤ�
// Called when the game starts (currently empty)
// ====================================
void ADeathzoneBASE::BeginPlay()
{
    Super::BeginPlay();
}
