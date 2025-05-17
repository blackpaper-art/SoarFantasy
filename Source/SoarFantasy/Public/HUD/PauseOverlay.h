// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseOverlay.generated.h"

/**
 * 
 */
UCLASS()
class SOARFANTASY_API UPauseOverlay : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* ResumeButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* MainMenuButton;
	
	UFUNCTION()
	void ResumeButtonClicked();
	UFUNCTION()
	void EndButtonClicked();

	//HUD
	UPROPERTY()
	class USFOverlay* SFOverlay;
	UPROPERTY()
	class UEndOverlay* EndOverlay;
};
