// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/Missile/MissileBASE.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/Kix/CharactersKix.h"

// ================================
// AMissileBASE
// �ߥ����뒤�ӤΌgװ
// Implementation for missile behavior
// ================================

// ���󥹥ȥ饯��
// Constructor: set up components
AMissileBASE::AMissileBASE()
{
    PrimaryActorTick.bCanEverTick = false;

    // �nͻ�� Sphere
    // Sphere component for collision detection
    MissileSphere = CreateDefaultSubobject<USphereComponent>(TEXT("MissileSphere"));
    RootComponent = MissileSphere;

    // ��å���򥢥��å�
    // Attach mesh to sphere
    MissileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MissileMesh"));
    MissileMesh->SetupAttachment(MissileSphere);

    // �Ƅӥ���ݩ`�ͥ��
    // Projectile movement component
    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
}

// ���`���_ʼ�r���������������nͻ�ж���Х����
// Play launch sound and bind overlap event on start
void AMissileBASE::BeginPlay()
{
    Super::BeginPlay();

    UGameplayStatics::PlaySound2D(GetWorld(), MissileLaunchedSound);

    // Sphere overlap ���٥�Ȥ�Х����
    // Bind sphere overlap event
    MissileSphere->OnComponentBeginOverlap.AddDynamic(this, &AMissileBASE::OnSphereOverlap);
}

// �nͻ������ץ쥤��`������������
// If overlaps player, trigger player death
void AMissileBASE::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    ACharactersKix* CharacterKix = Cast<ACharactersKix>(GetWorld()->GetFirstPlayerController()->GetPawn());
    if (CharacterKix)
    {
        CharacterKix->KixDead();
    }
}
