// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Kix/CharactersKix.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "HUD/SFHUD.h"
#include "HUD/SFOverlay.h"
#include "HUD/PauseOverlay.h"
#include "HUD/EndOverlay.h"
#include "Items/CoinBASE.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "SystemItems/SysSaveGame.h"
#include "WorldPartition/DataLayer/DataLayerSubsystem.h"
#include "WorldPartition/DataLayer/DataLayerInstance.h"

ACharactersKix::ACharactersKix()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	MainPlatformCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlatfromCamera"));

	//Initialize Components
	if (SpringArm)
	{
		SpringArm->SetupAttachment(GetRootComponent());
		SpringArm->TargetArmLength = 1000.f;
		SpringArm->SetWorldRotation(FRotator(0, -90, 0));
	}

	if (MainPlatformCamera)
	{
		MainPlatformCamera->SetupAttachment(SpringArm);
		MainPlatformCamera->SetWorldLocation(FVector(0, 700, 200));
	}

	JumpMaxCount = 2;
}

void ACharactersKix::BeginPlay()
{
	Super::BeginPlay();
	
	InitializeSFOverlay();
	GetWorldTimerManager().SetTimer(AddDistanceScoreHandle, this, &ACharactersKix::AddDistanceScore, .2f, true);

	SwitchToNormalMap();

	bIsStuck = false;
	StartLocation = GetActorLocation();

}


void ACharactersKix::Tick(float DeltaTime)
{
	UpdateMakeCoinMovetoPlayer();
	CurrentLocation = GetActorLocation();

	if (!bIsStuck)
	{
		FVector NewLocation = FMath::VInterpTo(CurrentLocation, StartLocation, DeltaTime, .5f);
		SetActorLocation(NewLocation);
	}
	GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Red, CurrentLocation.ToString());
	GEngine->AddOnScreenDebugMessage(2, 1.f, FColor::Blue, CurrentLocation.ToString());
	GEngine->AddOnScreenDebugMessage(3, 1.f, FColor::Black, StartLocation.ToString());

	if (StartLocation.X - CurrentLocation.X >= 1200 || CurrentLocation.Z <= 0)
	{
		KixDead();
	}
}

void ACharactersKix::UpdateMakeCoinMovetoPlayer()
{
	if (bMagnetActive)
	{
		TArray<AActor*> FoundCoins;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACoinBASE::StaticClass(), FoundCoins);
		for (AActor* Actor : FoundCoins)
		{
			ACoinBASE* Coin = Cast<ACoinBASE>(Actor);
			if (Coin)
			{
				float Distance = FVector::Dist(Coin->GetActorLocation(), GetActorLocation());
				if (Distance <= 500.f)
				{
					Coin->ActivateMagnet(GetActorLocation());
				}
			}
		}
	}
}


void ACharactersKix::Jump()
{
	if (CanJump())
	{
		const bool bWillBeDoubleJump = (JumpCurrentCount + 1 == JumpMaxCount);

		Super::Jump();

		bDoingDoubleJump = bWillBeDoubleJump;

		GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green,
			FString::Printf(TEXT("bDoingDoubleJump: %s"), bDoingDoubleJump ? TEXT("true") : TEXT("false")));
	}
}

void ACharactersKix::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	bDoingDoubleJump = false;
}

void ACharactersKix::Down()
{
	LaunchCharacter(FVector(0.f, 0.f, -2000.f), true, true);
}

void ACharactersKix::Dash()
{
	/*bIsDash = true;
	FVector Forward = GetActorForwardVector();
	Forward * 2500.f;
	LaunchCharacter(Forward, true, true);
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("Forward: %s"), *Forward.ToString()));*/
}

void ACharactersKix::AddCoinScore(int32 Score)
{
	CoinScore += Score;
	PerformanceScore = CoinScore + DistanceScore * 12;
	CurrentScore = CoinScore * 8 + PerformanceScore;
	SFOverlay->SetPerformanceScore(PerformanceScore);


	if (SFOverlay && bBonusTime == false)
	{
		BarCurrentScore += Score;
		BarPercent = BarCurrentScore / MaxCoinBarValue;
		SFOverlay->SetCoinProgressBarPercent(BarPercent);

		if (BarPercent >= 1.0f)
		{
			BarPercent = 1.f;
			SFOverlay->SetCoinProgressBarPercent(BarPercent);
			
			SetBonusTimeTrue();
			SwitchToBonusMap();
		}
		if (bBonusTime)
		{
			PerformanceScore = CoinScore * 2 + DistanceScore * 12;
		}
	}
}

void ACharactersKix::SwitchToBonusMap()
{
	UWorld* World = GetWorld();
	if (!World) return;

	UDataLayerSubsystem* DataLayerSubsystem = World->GetSubsystem<UDataLayerSubsystem>();
	if (!DataLayerSubsystem) return;


	if (MainLevelLayerAsset)
	{
		if (UDataLayerInstance* MainLayer = DataLayerSubsystem->GetDataLayerInstance(MainLevelLayerAsset))
		{
			DataLayerSubsystem->SetDataLayerRuntimeState(MainLayer,
				EDataLayerRuntimeState::Loaded);
		}
	}
	if (BonusLevelLayerAsset)
	{
		if (UDataLayerInstance* BonusLayer = DataLayerSubsystem->GetDataLayerInstance(BonusLevelLayerAsset))
		{
			DataLayerSubsystem->SetDataLayerRuntimeState(BonusLayer,
				EDataLayerRuntimeState::Activated);
		}
	}
}

void ACharactersKix::SwitchToNormalMap()
{
	UWorld* World = GetWorld();
	if (!World) return;

	UDataLayerSubsystem* DataLayerSubsystem = World->GetSubsystem<UDataLayerSubsystem>();
	if (!DataLayerSubsystem) return;

	if (MainLevelLayerAsset)
	{
		if (UDataLayerInstance* MainLayer = DataLayerSubsystem->GetDataLayerInstance(MainLevelLayerAsset))
		{
			DataLayerSubsystem->SetDataLayerRuntimeState(MainLayer,
				EDataLayerRuntimeState::Activated);
		}
	}
	if (BonusLevelLayerAsset)
	{
		if (UDataLayerInstance* BonusLayer = DataLayerSubsystem->GetDataLayerInstance(BonusLevelLayerAsset))
		{
			DataLayerSubsystem->SetDataLayerRuntimeState(BonusLayer,
				EDataLayerRuntimeState::Loaded);
		}
	}
}

void ACharactersKix::ActiveKixsMag()
{
	if (bMagnetActive)
	{
		return;
	}
	bMagnetActive = true;

	GetWorld()->GetTimerManager().SetTimer(MagnetTimerHandle, this, &ACharactersKix::DeactivateKixsMag, 30.f, false);
}

void ACharactersKix::InitializeSFOverlay()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		ASFHUD* SFHUD = Cast<ASFHUD>(PlayerController->GetHUD());
		if (SFHUD)
		{
			SFOverlay = SFHUD->GetSFOverlay();
			if (SFOverlay)
			{
				SFOverlay->SetCoinProgressBarPercent(CurrentScore / MaxCoinBarValue);
				SFOverlay->SetPerformanceScore(PerformanceScore);
				SFOverlay->SetDistanceScore(DistanceScore);
			}
		}
	}
}

void ACharactersKix::SetBonusTimeTrue()
{
	bBonusTime = true;
	float BonusDurationTime = 10.f;
	GetWorldTimerManager().SetTimer(SetBonusTimeHandle, this, &ACharactersKix::SetBonusTimeFalse, BonusDurationTime, false);
}

void ACharactersKix::SetBonusTimeFalse()
{
	SwitchToNormalMap();

	bBonusTime = false;

	BarPercent = 0.f;
	BarCurrentScore = 0.f;
	if (SFOverlay)
	{
		SFOverlay->SetCoinProgressBarPercent(0.f);
	}
}

void ACharactersKix::AddDistanceScore()
{
	DistanceScore += 1;
	PerformanceScore = CoinScore + DistanceScore * 12;
	CurrentScore = CoinScore * 8 + PerformanceScore;
	SFOverlay->SetDistanceScore(DistanceScore);
}

void ACharactersKix::DeactivateKixsMag()
{
	bMagnetActive = false;
	SwitchToNormalMap();
}

void ACharactersKix::OpenOrClosePauseGameMenu(bool bPauseMenuActivating)
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		ASFHUD* SFHUD = Cast<ASFHUD>(PlayerController->GetHUD());
		if (SFHUD)
		{
			if (bPauseMenuActivating)
			{
				SFHUD->OnOffPauseOverlay(bPauseMenuActivating);
			}
			else if (!bPauseMenuActivating)
			{
				SFHUD->OnOffPauseOverlay(bPauseMenuActivating);
			}
		}
	}
}


void ACharactersKix::OpenEndMenu()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		PlayerController->SetShowMouseCursor(true);
		ASFHUD* SFHUD = Cast<ASFHUD>(PlayerController->GetHUD());
		if (SFHUD)
		{
			SFHUD->OnOffEndOverlay(true);
			bOtherOverlayIsActivated = true;
			EndOverlay = SFHUD->GetEndOverlay();
			if (EndOverlay)
			{
				//Display BestScore to Overlay via SaveGame
				const FString SlotName = TEXT("PlayerSaveSlot");
				const int32 UserIndex = 0;
				USysSaveGame* SaveGame = Cast<USysSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));
				if (SaveGame)
				{
					EndOverlay->SetBestScore(SaveGame->BestScore);
				}
				EndOverlay->SetCurrentScore(this->GetPlayerCurrentScore());
				EndOverlay->SetCoinScore(this->GetPlayerCoinScoreScore());
				EndOverlay->SetPerformanceScore(this->GetPlayerPerformanceScore());
				EndOverlay->SetDistancetScore(this->GetPlayerDistanceScore());
			}
		}
	}
}

void ACharactersKix::KixDead()
{
	UGameplayStatics::PlaySound2D(GetWorld(), DeadSound);
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	//Save BestScore via SaveGame
	USysSaveGame::TrySaveBestScore(CurrentScore);
	OpenEndMenu();
}
