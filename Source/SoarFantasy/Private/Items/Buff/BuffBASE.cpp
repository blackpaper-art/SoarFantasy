// Fill out your copyright notice in the Description page of Project Settings.

// ================================
// ABuffBASE
// �Хդλ������饹
// Base class for Buff items
// ================================

#include "Items/Buff/BuffBASE.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Characters/Kix/CharactersKix.h"

ABuffBASE::ABuffBASE()
{
	// ���Υ������`�� Tick ���Ҫ�Ȥ��ʤ�
	// This actor does not need ticking every frame
	PrimaryActorTick.bCanEverTick = false;

	// ��å�������ɤ���Root ���O��
	// Create Static Mesh and set it as Root
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MissileMesh"));
	RootComponent = StaticMesh;

	// �������ж����٥�Ȥ�Х����
	// Bind overlap event
	StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &ABuffBASE::OverlapBegin);

	// �Ƅӥ���ݩ`�ͥ�Ȥ�����
	// Create projectile movement component
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
}

void ABuffBASE::BeginPlay()
{
	Super::BeginPlay();
	
}

// ���`�Щ`��åװk���r�΄I��
// Called when another actor overlaps this actor
void ABuffBASE::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		// Kix ����饯���`���ж�
		// Check if the overlapped actor is a Kix character
		ACharactersKix* KixCharacter = Cast<ACharactersKix>(OtherActor);
		if (KixCharacter)
		{
			// �Хդ��m�ä���
			// Activate the buff effect
			KixCharacter->ActiveKixsMag();

			// ���Υ������`���Ɨ�
			// Destroy this buff actor
			Destroy();
		}
	}
}

