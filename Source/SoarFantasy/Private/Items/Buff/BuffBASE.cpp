// Fill out your copyright notice in the Description page of Project Settings.

// ================================
// ABuffBASE
// バフの児云クラス
// Base class for Buff items
// ================================

#include "Items/Buff/BuffBASE.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Characters/Kix/CharactersKix.h"

ABuffBASE::ABuffBASE()
{
	// このアクタ�`は Tick を駅勣としない
	// This actor does not need ticking every frame
	PrimaryActorTick.bCanEverTick = false;

	// メッシュを伏撹し、Root に�O協
	// Create Static Mesh and set it as Root
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MissileMesh"));
	RootComponent = StaticMesh;

	// 輝たり登協イベントをバインド
	// Bind overlap event
	StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &ABuffBASE::OverlapBegin);

	// 卞�咼灰鵐櫞`ネントを伏撹
	// Create projectile movement component
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
}

void ABuffBASE::BeginPlay()
{
	Super::BeginPlay();
	
}

// オ�`バ�`ラップ�k伏�rの�I尖
// Called when another actor overlaps this actor
void ABuffBASE::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		// Kix キャラクタ�`か登協
		// Check if the overlapped actor is a Kix character
		ACharactersKix* KixCharacter = Cast<ACharactersKix>(OtherActor);
		if (KixCharacter)
		{
			// バフを�m喘する
			// Activate the buff effect
			KixCharacter->ActiveKixsMag();

			// このアクタ�`を篤��
			// Destroy this buff actor
			Destroy();
		}
	}
}

