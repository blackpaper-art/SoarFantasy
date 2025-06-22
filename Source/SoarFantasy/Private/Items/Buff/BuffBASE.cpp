// Fill out your copyright notice in the Description page of Project Settings.

// ================================
// ABuffBASE
// バフの基本クラス
// Base class for Buff items
// ================================

#include "Items/Buff/BuffBASE.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Characters/Kix/CharactersKix.h"

ABuffBASE::ABuffBASE()
{
	// このアクターは Tick を必要としない
	// This actor does not need ticking every frame
	PrimaryActorTick.bCanEverTick = false;

	// メッシュを生成し、Root に設定
	// Create Static Mesh and set it as Root
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MissileMesh"));
	RootComponent = StaticMesh;

	// 当たり判定イベントをバインド
	// Bind overlap event
	StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &ABuffBASE::OverlapBegin);

	// 移動コンポーネントを生成
	// Create projectile movement component
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
}

void ABuffBASE::BeginPlay()
{
	Super::BeginPlay();
	
}

// オーバーラップ発生時の処理
// Called when another actor overlaps this actor
void ABuffBASE::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		// Kix キャラクターか判定
		// Check if the overlapped actor is a Kix character
		ACharactersKix* KixCharacter = Cast<ACharactersKix>(OtherActor);
		if (KixCharacter)
		{
			// バフを適用する
			// Activate the buff effect
			KixCharacter->ActiveKixsMag();

			// このアクターを破棄
			// Destroy this buff actor
			Destroy();
		}
	}
}

