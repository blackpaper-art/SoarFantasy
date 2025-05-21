// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "KixPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class ACharactersKix;
/**
 * 
 */

UENUM(BlueprintType)
enum class EPauseUIState : uint8
{
	None UMETA(DisplayName = "None"),
	MainMenu UMETA(DisplayName = "Pause Main"),
	SubMenu UMETA(DisplayName = "Other Menu"),
};

UCLASS()
class SOARFANTASY_API AKixPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputMappingContext> CurrentMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> DownAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> DashAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> PauseAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<ACharactersKix> CurrentChara;

	void SetPauseBoolFalse();

	EPauseUIState CurrentPauseUIState = EPauseUIState::None;

protected:
	virtual void OnPossess(APawn* InPawn) override;
	void Jump();
	void PauseGame();
	void Down();
	void Dash();

private:
	bool bPauseMenuActivating = false;
};
