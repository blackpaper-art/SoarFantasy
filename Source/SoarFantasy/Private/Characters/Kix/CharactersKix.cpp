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

// ====================================
// コンストラクタ
// Constructor: initialize camera, spring arm, jump
// ====================================
ACharactersKix::ACharactersKix()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	MainPlatformCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlatfromCamera"));

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

// ====================================
// ゲーム開始時の初期化
// Initialize HUD, start distance timer, switch to normal map
// ====================================
void ACharactersKix::BeginPlay()
{
	Super::BeginPlay();

	InitializeSFOverlay();
	GetWorldTimerManager().SetTimer(AddDistanceScoreHandle, this, &ACharactersKix::AddDistanceScore, .2f, true);

	SwitchToNormalMap();

	bIsStuck = false;
	StartLocation = GetActorLocation();
}

// ====================================
// 毎フレーム更新
// Update magnet effect, smooth reposition, check death condition
// ====================================
void ACharactersKix::Tick(float DeltaTime)
{
	UpdateMakeCoinMovetoPlayer();
	CurrentLocation = GetActorLocation();

	if (!bIsStuck)
	{
		FVector NewLocation = FMath::VInterpTo(CurrentLocation, StartLocation, DeltaTime, .5f);
		SetActorLocation(NewLocation);
	}

	// プレイヤーが後ろに下がりすぎ or 落下したら死亡
	if (StartLocation.X - CurrentLocation.X >= 1200 || CurrentLocation.Z <= 0)
	{
		KixDead();
	}
}

// ====================================
// マグネット効果: 近くのコインを吸引
// ====================================
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

// ====================================
// ジャンプ入力: ダブルジャンプ判定
// ====================================
void ACharactersKix::Jump()
{
	if (CanJump())
	{
		const bool bWillBeDoubleJump = (JumpCurrentCount + 1 == JumpMaxCount);
		Super::Jump();
		bDoingDoubleJump = bWillBeDoubleJump;
	}
}

// ====================================
// 着地時: ダブルジャンプフラグリセット
// ====================================
void ACharactersKix::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	bDoingDoubleJump = false;
}

// ====================================
// ダウン入力: 強制的に下方向へ
// ====================================
void ACharactersKix::Down()
{
	LaunchCharacter(FVector(0.f, 0.f, -2000.f), true, true);
}

// ====================================
// ダッシュ入力（未実装）
// ====================================
void ACharactersKix::Dash()
{
	// 構造のみ用意
}

// ====================================
// コインスコア加算 & パフォーマンススコア更新
// ====================================
void ACharactersKix::AddCoinScore(int32 Score)
{
	CoinScore += Score;
	PerformanceScore = CoinScore + DistanceScore * 12;
	CurrentScore = CoinScore * 8 + PerformanceScore;
	SFOverlay->SetPerformanceScore(PerformanceScore);

	if (SFOverlay && !bBonusTime)
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

// ====================================
// ボーナスマップへ切替
// ====================================
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
			DataLayerSubsystem->SetDataLayerRuntimeState(MainLayer, EDataLayerRuntimeState::Loaded);
		}
	}
	if (BonusLevelLayerAsset)
	{
		if (UDataLayerInstance* BonusLayer = DataLayerSubsystem->GetDataLayerInstance(BonusLevelLayerAsset))
		{
			DataLayerSubsystem->SetDataLayerRuntimeState(BonusLayer, EDataLayerRuntimeState::Activated);
		}
	}
}

// ====================================
// 通常マップへ切替
// ====================================
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
			DataLayerSubsystem->SetDataLayerRuntimeState(MainLayer, EDataLayerRuntimeState::Activated);
		}
	}
	if (BonusLevelLayerAsset)
	{
		if (UDataLayerInstance* BonusLayer = DataLayerSubsystem->GetDataLayerInstance(BonusLevelLayerAsset))
		{
			DataLayerSubsystem->SetDataLayerRuntimeState(BonusLayer, EDataLayerRuntimeState::Loaded);
		}
	}
}

// ====================================
// マグネット有効化（15秒）
// ====================================
void ACharactersKix::ActiveKixsMag()
{
	if (bMagnetActive) return;
	bMagnetActive = true;
	GetWorld()->GetTimerManager().SetTimer(MagnetTimerHandle, this, &ACharactersKix::DeactivateKixsMag, 15.f, false);
}

// ====================================
// HUDオーバーレイ初期化
// ====================================
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

// ====================================
// ボーナスタイム開始
// ====================================
void ACharactersKix::SetBonusTimeTrue()
{
	bBonusTime = true;
	GetWorldTimerManager().SetTimer(SetBonusTimeHandle, this, &ACharactersKix::SetBonusTimeFalse, 10.f, false);
}

// ====================================
// ボーナスタイム終了 & 状態リセット
// ====================================
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

// ====================================
// 距離スコア加算
// ====================================
void ACharactersKix::AddDistanceScore()
{
	DistanceScore += 1;
	PerformanceScore = CoinScore + DistanceScore * 12;
	CurrentScore = CoinScore * 8 + PerformanceScore;
	SFOverlay->SetDistanceScore(DistanceScore);
}

// ====================================
// マグネット無効化
// ====================================
void ACharactersKix::DeactivateKixsMag()
{
	bMagnetActive = false;
}

// ====================================
// ポーズメニュー開閉
// ====================================
void ACharactersKix::OpenOrClosePauseGameMenu(bool bPauseMenuActivating)
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		ASFHUD* SFHUD = Cast<ASFHUD>(PlayerController->GetHUD());
		if (SFHUD)
		{
			SFHUD->OnOffPauseOverlay(bPauseMenuActivating);
		}
	}
}

// ====================================
// エンドメニューを開いてスコア表示
// ====================================
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

// ====================================
// 死亡時処理: 音再生、スコア保存、エンドメニューへ
// ====================================
void ACharactersKix::KixDead()
{
	UGameplayStatics::PlaySound2D(GetWorld(), DeadSound);
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	USysSaveGame::TrySaveBestScore(CurrentScore);
	OpenEndMenu();
}
