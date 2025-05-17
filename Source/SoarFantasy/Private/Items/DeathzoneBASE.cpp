#include "Items/DeathzoneBASE.h"
#include "Components/BoxComponent.h"

ADeathzoneBASE::ADeathzoneBASE()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxCollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollisionComp"));
	RootComponent = BoxCollisionComp;
	BoxCollisionComp->SetBoxExtent(FVector(250.f, 250.f, 50.f));
}

void ADeathzoneBASE::BeginPlay()
{
	Super::BeginPlay();
	
}

