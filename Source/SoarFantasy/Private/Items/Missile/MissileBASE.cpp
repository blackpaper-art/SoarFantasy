// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/Missile/MissileBASE.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/Kix/CharactersKix.h"

// ================================
// AMissileBASE
// ミサイル挙動の実装
// Implementation for missile behavior
// ================================

// コンストラクタ
// Constructor: set up components
AMissileBASE::AMissileBASE()
{
    PrimaryActorTick.bCanEverTick = false;

    // 衝突用 Sphere
    // Sphere component for collision detection
    MissileSphere = CreateDefaultSubobject<USphereComponent>(TEXT("MissileSphere"));
    RootComponent = MissileSphere;

    // メッシュをアタッチ
    // Attach mesh to sphere
    MissileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MissileMesh"));
    MissileMesh->SetupAttachment(MissileSphere);

    // 移動コンポーネント
    // Projectile movement component
    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
}

// ゲーム開始時に音を再生し、衝突判定をバインド
// Play launch sound and bind overlap event on start
void AMissileBASE::BeginPlay()
{
    Super::BeginPlay();

    UGameplayStatics::PlaySound2D(GetWorld(), MissileLaunchedSound);

    // Sphere overlap イベントをバインド
    // Bind sphere overlap event
    MissileSphere->OnComponentBeginOverlap.AddDynamic(this, &AMissileBASE::OnSphereOverlap);
}

// 衝突したらプレイヤーを死亡させる
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
