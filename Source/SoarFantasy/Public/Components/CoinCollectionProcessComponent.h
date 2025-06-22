// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CoinCollectionProcessComponent.generated.h"

/**
 * ====================================
 * UCoinCollectionProcessComponent
 * �����󅧼����M�Ф�����륳��ݩ`�ͥ��
 * Component to manage coin collection progress
 * ====================================
 */

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOARFANTASY_API UCoinCollectionProcessComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// ���󥹥ȥ饯��
	// Constructor
	UCoinCollectionProcessComponent();

	// ���ե�`����Ф��
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;		

protected:
	virtual void BeginPlay() override;

private:
	// �F�ڤΥ�������
	// Current coin percent
	UPROPERTY(EditAnywhere, Category = "Coin Percent")
	float CurrentCoinPercent;

	// ��󥳥�����
	// Maximum coin percent
	UPROPERTY(EditAnywhere, Category = "Coin Percent")
	float MaxCoinPercent;
};
