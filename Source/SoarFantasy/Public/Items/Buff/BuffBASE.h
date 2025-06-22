// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuffBASE.generated.h"

// ================================
// ABuffBASE
// バフの基本クラス
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
    // ゲーム開始時に呼ばれる
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // 衝突判定用の SphereComponent
    // Sphere component for collision detection
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
    class USphereComponent* Sphere;

    // 見た目を担当する StaticMeshComponent
    // Visual representation
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
    class UStaticMeshComponent* StaticMesh;

    // 投射移動を制御する ProjectileMovementComponent
    // Controls projectile-like movement
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    class UProjectileMovementComponent* ProjectileMovementComponent;

    // オーバーラップ開始時に呼ばれる関数
    // Called when overlap begins with another actor
    UFUNCTION()
    void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
