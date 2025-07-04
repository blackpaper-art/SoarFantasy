// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuffBASE.generated.h"

// ================================
// ABuffBASE
// バフの児云クラス
// Base class for Buff items
// ================================

UCLASS()
class SOARFANTASY_API ABuffBASE : public AActor
{
    GENERATED_BODY()

public:
    // コンストラクタ
    // Constructor
    ABuffBASE();

protected:
    // ゲ�`ム�_兵�rに柵ばれる
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // �n融登協喘の SphereComponent
    // Sphere component for collision detection
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
    class USphereComponent* Sphere;

    // ��た朕を毅輝する StaticMeshComponent
    // Visual representation
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
    class UStaticMeshComponent* StaticMesh;

    // 誘符卞�咾鰆酉�する ProjectileMovementComponent
    // Controls projectile-like movement
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    class UProjectileMovementComponent* ProjectileMovementComponent;

    // オ�`バ�`ラップ�_兵�rに柵ばれる�v方
    // Called when overlap begins with another actor
    UFUNCTION()
    void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
