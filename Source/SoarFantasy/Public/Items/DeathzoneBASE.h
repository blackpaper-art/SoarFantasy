#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DeathzoneBASE.generated.h"

/**
 * ====================================
 * ADeathzoneBASE
 * •◊•Ï•§•‰©`§¨¥•§Ï§Î§»º¥À¿•æ©`•Û
 * Kill zone: player dies upon overlap
 * ====================================
 */
UCLASS()
class SOARFANTASY_API ADeathzoneBASE : public AActor
{
    GENERATED_BODY()

public:
    // •≥•Û•π•»•È•Ø•ø
    // Constructor
    ADeathzoneBASE();

protected:
    // •≤©`•‡È_ ºïr
    // Called when the game starts
    virtual void BeginPlay() override;

    // •«•π•æ©`•Û§Œµ±§ø§Í≈–∂®•‹•√•Ø•π
    // Box collision for kill zone
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
    class UBoxComponent* BoxCollisionComp;
};
