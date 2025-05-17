// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CoinCollectionProcessComponent.h"

UCoinCollectionProcessComponent::UCoinCollectionProcessComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UCoinCollectionProcessComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UCoinCollectionProcessComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

