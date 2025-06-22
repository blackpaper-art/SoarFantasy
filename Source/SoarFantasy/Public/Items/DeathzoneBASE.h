#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DeathzoneBASE.generated.h"

/**
 * ====================================
 * ADeathzoneBASE
 * �ץ쥤��`�������ȼ������`��
 * Kill zone: player dies upon overlap
 * ====================================
 */
UCLASS()
class SOARFANTASY_API ADeathzoneBASE : public AActor
{
    GENERATED_BODY()

public:
    // ���󥹥ȥ饯��
    // Constructor
    ADeathzoneBASE();

protected:
    // ���`���_ʼ�r
    // Called when the game starts
    virtual void BeginPlay() override;

    // �ǥ����`��ε������ж��ܥå���
    // Box collision for kill zone
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
    class UBoxComponent* BoxCollisionComp;
};
