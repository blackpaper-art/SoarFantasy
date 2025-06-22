// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SystemItems/SoarFantasyInterface.h"
#include "CoinBASE.generated.h"

/**
 * ====================================
 * ACoinBASE
 * ����������������`
 * Base actor for collectible coins
 * ====================================
 */
UCLASS()
class SOARFANTASY_API ACoinBASE : public AActor, public ISoarFantasyInterface
{
    GENERATED_BODY()

public:
    // ���󥹥ȥ饯��
    // Constructor
    ACoinBASE();

    // ���ե�`����Ф��
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // �������Ҋ��Ŀ
    // Visual mesh component for the coin
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
    class UStaticMeshComponent* StaticMeshComp;

    // ������λ���������
    // Base score value for the coin
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
    int32 CoinScore = 1;

    // ����������
    // Score multiplier
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
    int32 CoinSocreRate = 1;

    // �����ե饰
    // Whether magnet is active
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magnet")
    bool bMagnetActive;

    // �������`���å�λ��
    // Target location for magnet attraction
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magnet")
    FVector MagnetCoinTargetLocation;

    // �������Є���
    // Activate magnet effect
    void ActivateMagnet(const FVector& TargetLocation);

    // ������o����
    // Deactivate magnet effect
    void DeactivateMagnet();

protected:
    // ���`���_ʼ�r�˺��Ф��
    // Called when the game starts
    virtual void BeginPlay() override;

    // ������ȡ����
    // Sound played when coin is collected
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    class USoundBase* CoinCollectionSound;

    // ���`�Щ`��å��_ʼ�r�΄I��
    // Called when overlap begins
    UFUNCTION()
    void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
    // �������ƄӤ����ٶ�
    // Speed when magnet is active
    float MagnetCoinSpeed = 1000.f;
};
