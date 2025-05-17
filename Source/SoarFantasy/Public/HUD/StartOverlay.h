// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartOverlay.generated.h"

/**
 * 
 */
UCLASS()
class SOARFANTASY_API UStartOverlay : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* PlayButton;

	UFUNCTION()
	void StartGameButton();
};
