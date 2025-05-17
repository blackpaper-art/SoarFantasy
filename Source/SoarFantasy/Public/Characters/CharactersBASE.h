// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharactersBASE.generated.h"

UCLASS()
class SOARFANTASY_API ACharactersBASE : public ACharacter
{
	GENERATED_BODY()

public:
	ACharactersBASE();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;
};
