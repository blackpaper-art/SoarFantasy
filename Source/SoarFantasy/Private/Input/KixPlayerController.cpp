// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/KixPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Characters/Kix/CharactersKix.h"
#include "GameFramework/CharacterMovementComponent.h"

void AKixPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(InputComponent);

	if (EnhancedInputComp)
	{
		//Jump
		EnhancedInputComp->BindAction(JumpAction, ETriggerEvent::Started, this, &AKixPlayerController::Jump);
		//Down
		EnhancedInputComp->BindAction(DownAction, ETriggerEvent::Started, this, &AKixPlayerController::Down);
		//Dash
		EnhancedInputComp->BindAction(DashAction, ETriggerEvent::Started, this, &AKixPlayerController::Dash);
		//Pause
		EnhancedInputComp->BindAction(PauseAction, ETriggerEvent::Started, this, &AKixPlayerController::PauseGame);
	}
}


void AKixPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	CurrentChara = Cast<ACharactersKix>(InPawn);

	if (ULocalPlayer* LP = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			Subsystem->AddMappingContext(CurrentMappingContext, 0);
		}
	}
}

void AKixPlayerController::Jump()
{
	CurrentChara->Jump();
}

void AKixPlayerController::PauseGame()
{
	if (CurrentPauseUIState == EPauseUIState::SubMenu)
	{
		return;
	}

	if (!bPauseMenuActivating && !CurrentChara->GetOtherOverlayActivating())
	{
		SetPause(true);
		bPauseMenuActivating = true;
		FInputModeUIOnly InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		SetInputMode(InputMode);

		CurrentPauseUIState = EPauseUIState::MainMenu;
		CurrentChara->OpenOrClosePauseGameMenu(true);
	}
	else if(bPauseMenuActivating && CurrentPauseUIState == EPauseUIState::MainMenu) 
	{
		bPauseMenuActivating = false;
		SetPause(false);
		FInputModeGameOnly InputMode;
		SetInputMode(InputMode);
		bPauseMenuActivating = false;

		CurrentPauseUIState = EPauseUIState::None;
		CurrentChara->OpenOrClosePauseGameMenu(false);
	}
}

void AKixPlayerController::Down()
{
	CurrentChara->Down();
}

void AKixPlayerController::Dash()
{
	CurrentChara->Dash();
}

void AKixPlayerController::SetPauseBoolFalse()
{
	bPauseMenuActivating = false;
	CurrentPauseUIState = EPauseUIState::None;
}