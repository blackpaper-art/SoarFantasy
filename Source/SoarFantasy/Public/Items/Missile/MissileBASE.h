// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MissileBASE.generated.h"

/**
 * ====================================
 * AMissileBASE
 * 飛行ミサイルアクター
 * Flying missile actor
 * ====================================
 */
UCLASS()
class SOARFANTASY_API AMissileBASE : public AActor
{
    GENERATED_BODY()

public:
    // コンストラクタ
    // Constructor
    AMissileBASE();

protected:
    // ゲーム開始時に呼ばれる
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // 当たり判定用 Sphere
    // Sphere component for collision
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
    class USphereComponent* MissileSphere;

    // ミサイルのメッシュ
    // Visual mesh for the missile
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
    class UStaticMeshComponent* MissileMesh;

    // ミサイルの移動コンポーネント
    // Projectile movement component
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    class UProjectileMovementComponent* ProjectileMovementComponent;

    // ミサイル発射音
    // Sound when missile is launched
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    class USoundBase* MissileLaunchedSound;

    // 衝突時の処理
    // Called when sphere overlaps another actor
    UFUNCTION()
    void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
