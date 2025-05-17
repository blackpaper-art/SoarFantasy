// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SFHUD.generated.h"

/**
 * 
 */
UCLASS()
class SOARFANTASY_API ASFHUD : public AHUD
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "SoarFantasy")
	TSubclassOf<class USFOverlay> USFOverlayClass;
	UPROPERTY(EditDefaultsOnly, Category = "SoarFantasy")
	USFOverlay* SFOverlay;

	UPROPERTY(EditDefaultsOnly, Category = "PauseMenu")
	TSubclassOf<class UPauseOverlay> UPauseOverlayClass;
	UPROPERTY(EditDefaultsOnly, Category = "PauseMenu")
	UPauseOverlay* PauseOverlay;

	UPROPERTY(EditDefaultsOnly, Category = "EndMenu")
	TSubclassOf<class UEndOverlay> UEndOverlayClass;
	UPROPERTY(EditDefaultsOnly, Category = "EndMenu")
	UEndOverlay* EndOverlay;

	UPROPERTY(EditDefaultsOnly, Category = "StartMenu")
	TSubclassOf<class UStartOverlay> UStartOverlayClass;
	UPROPERTY(EditDefaultsOnly, Category = "StartMenu")
	UStartOverlay* StartOverlay;

public:
	FORCEINLINE USFOverlay* GetSFOverlay() const { return SFOverlay; }
	FORCEINLINE UEndOverlay* GetEndOverlay() const { return EndOverlay; }
	FORCEINLINE UStartOverlay* GetStartOverlay() const { return StartOverlay; }
	void OnOffPauseOverlay(bool bOnOff);
	void OnOffEndOverlay(bool bOnOff);
	void OnOffStartOverlay(bool bOnOff);
};
