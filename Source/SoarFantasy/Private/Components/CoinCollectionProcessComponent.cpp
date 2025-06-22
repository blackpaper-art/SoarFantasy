// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/CoinCollectionProcessComponent.h"

// ================================
// UCoinCollectionProcessComponent
// �����󅧼��M�й���Όgװ
// Implementation of coin collection process component
// ================================

// ���󥹥ȥ饯����Tick ���Є���
// Constructor: enable ticking
UCoinCollectionProcessComponent::UCoinCollectionProcessComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

// ���`���_ʼ�r�γ��ڻ�
// Initialization when the game starts
void UCoinCollectionProcessComponent::BeginPlay()
{
    Super::BeginPlay();
}

// ���ե�`����Ф��I��
// Called every frame
void UCoinCollectionProcessComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // �����󅧼����M�Х��å��򤳤���ӛ��
    // Add coin collection progress logic here
}
