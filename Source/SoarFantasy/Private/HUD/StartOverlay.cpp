// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/StartOverlay.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/Kix/CharactersKix.h"

void UStartOverlay::NativeConstruct()
{
	if (PlayButton)
	{
		PlayButton->OnClicked.AddDynamic(this, &UStartOverlay::StartGameButton);
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
