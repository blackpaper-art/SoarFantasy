// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CoinCollectionProcessComponent.generated.h"

/**
 * ====================================
 * UCoinCollectionProcessComponent
 * コイン収集の進行を管理するコンポーネント
 * Component to manage coin collection progress
 * ====================================
 */

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOARFANTASY_API UCoinCollectionProcessComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// コンストラクタ
	// Constructor
	UCoinCollectionProcessComponent();

	// 毎フレーム呼ばれる
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;		

protected:
	virtual void BeginPlay() override;

private:
	// 現在のコイン割合
	// Current coin percent
	UPROPERTY(EditAnywhere, Category = "Coin Percent")
	float CurrentCoinPercent;

	// 最大コイン割合
	// Maximum coin percent
	UPROPERTY(EditAnywhere, Category = "Coin Percent")
	float MaxCoinPercent;
};
