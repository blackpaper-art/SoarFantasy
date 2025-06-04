// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/StartOverlay.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Characters/Kix/CharactersKix.h"

void UStartOverlay::NativeConstruct()
{
	if (PlayButton)
	{
		PlayButton->OnClicked.AddDynamic(this, &UStartOverlay::StartGameButton);
	}
	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UStartOverlay::QuitGameButton);
	}
}

void UStartOverlay::StartGameButton()
{
	RemoveFromParent();

	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		PlayerController->SetPause(false);
		PlayerController->SetShowMouseCursor(false);
		PlayerController->SetInputMode(FInputModeGameOnly());
	}

	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void UStartOverlay::QuitGameButton()
{
	RemoveFromParent();


	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		UKismetSystemLibrary::QuitGame(this, PlayerController, EQuitPreference::Quit, false);
	}
}
