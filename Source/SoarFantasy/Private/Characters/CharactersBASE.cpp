// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CharactersBASE.h"

ACharactersBASE::ACharactersBASE()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACharactersBASE::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharactersBASE::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharactersBASE::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

