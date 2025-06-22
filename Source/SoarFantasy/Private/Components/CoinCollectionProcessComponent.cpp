// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/CoinCollectionProcessComponent.h"

// ================================
// UCoinCollectionProcessComponent
// コイン収集進行管理の実装
// Implementation of coin collection process component
// ================================

// コンストラクタ：Tick を有効化
// Constructor: enable ticking
UCoinCollectionProcessComponent::UCoinCollectionProcessComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

// ゲーム開始時の初期化
// Initialization when the game starts
void UCoinCollectionProcessComponent::BeginPlay()
{
    Super::BeginPlay();
}

// 毎フレーム呼ばれる処理
// Called every frame
void UCoinCollectionProcessComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // コイン収集の進行ロジックをここに記述
    // Add coin collection progress logic here
}
