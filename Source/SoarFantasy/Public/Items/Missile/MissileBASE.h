// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MissileBASE.generated.h"

/**
 * ====================================
 * AMissileBASE
 * �w�Хߥ����륢�����`
 * Flying missile actor
 * ====================================
 */
UCLASS()
class SOARFANTASY_API AMissileBASE : public AActor
{
    GENERATED_BODY()

public:
    // ���󥹥ȥ饯��
    // Constructor
    AMissileBASE();

protected:
    // ���`���_ʼ�r�˺��Ф��
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // �������ж��� Sphere
    // Sphere component for collision
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
    class USphereComponent* MissileSphere;

    // �ߥ�����Υ�å���
    // Visual mesh for the missile
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
    class UStaticMeshComponent* MissileMesh;

    // �ߥ�������Ƅӥ���ݩ`�ͥ��
    // Projectile movement component
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    class UProjectileMovementComponent* ProjectileMovementComponent;

    // �ߥ�����k����
    // Sound when missile is launched
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    class USoundBase* MissileLaunchedSound;

    // �nͻ�r�΄I��
    // Called when sphere overlaps another actor
    UFUNCTION()
    void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
