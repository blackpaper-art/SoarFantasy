#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DeathzoneBASE.generated.h"

UCLASS()
class SOARFANTASY_API ADeathzoneBASE : public AActor
{
	GENERATED_BODY()
	
public:	
	ADeathzoneBASE();
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	class UBoxComponent* BoxCollisionComp;
};
