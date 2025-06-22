// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuffBASE.generated.h"

// ================================
// ABuffBASE
// �Хդλ������饹
// Base class for Buff items
// ================================

UCLASS()
class SOARFANTASY_API ABuffBASE : public AActor
{
    GENERATED_BODY()

public:
    // ���󥹥ȥ饯��
    // Constructor
    ABuffBASE();

protected:
    // ���`���_ʼ�r�˺��Ф��
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // �nͻ�ж��ä� SphereComponent
    // Sphere component for collision detection
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
    class USphereComponent* Sphere;

    // Ҋ��Ŀ�򵣵����� StaticMeshComponent
    // Visual representation
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
    class UStaticMeshComponent* StaticMesh;

    // Ͷ���ƄӤ��������� ProjectileMovementComponent
    // Controls projectile-like movement
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    class UProjectileMovementComponent* ProjectileMovementComponent;

    // ���`�Щ`��å��_ʼ�r�˺��Ф���v��
    // Called when overlap begins with another actor
    UFUNCTION()
    void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
