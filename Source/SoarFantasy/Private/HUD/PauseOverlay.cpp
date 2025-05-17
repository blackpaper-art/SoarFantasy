// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/PauseOverlay.h"
#include "Components/Button.h"
#include "Input/KixPlayerController.h"
#include "HUD/SFHUD.h"
#include "HUD/EndOverlay.h"
#include "Characters/Kix/CharactersKix.h"

void UPauseOverlay::NativeConstruct()
{
	if (ResumeButton)
	{
		ResumeButton->OnClicked.AddDynamic(this, &UPauseOverlay::ResumeButtonClicked);
	}
	if (MainMenuButton)
	{
		MainMenuButton->OnClicked.AddDynamic(this, &UPauseOverlay::EndButtonClicked);
	}
}

void UPauseOverlay::ResumeButtonClicked()
{
	if (GetWorld())
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

		if (PlayerController)
		{
			PlayerController->SetPause(false);
			PlayerController->SetShowMouseCursor(false);
			this->RemoveFromParent();
			AKixPlayerController* KixController = Cast<AKixPlayerController>(PlayerController);
			if (KixController)
			{
				KixController->SetPauseBoolFalse();
			}
		}
	}
}

void UPauseOverlay::EndButtonClicked()
{
	if (GetWorld())
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

		if (PlayerController)
		{
			ASFHUD* SFHUD = Cast<ASFHUD>(PlayerController->GetHUD());
			if (SFHUD)
			{
				SFHUD->OnOffEndOverlay(true);
				EndOverlay = SFHUD->GetEndOverlay();
				if (EndOverlay)
				{
					ACharactersKix* CharacterKix = Cast<ACharactersKix>(PlayerController->GetPawn());
					EndOverlay->SetBestScore(CharacterKix->GetPlayerCurrentScore());
					EndOverlay->SetCurrentScore(CharacterKix->GetPlayerCurrentScore());
					EndOverlay->SetCoinScore(CharacterKix->GetPlayerCoinScoreScore());
					EndOverlay->SetPerformanceScore(CharacterKix->GetPlayerPerformanceScore());
					EndOverlay->SetDistancetScore(CharacterKix->GetPlayerDistanceScore());
				}
				this->RemoveFromParent();
				
			}
		}
	}
}
