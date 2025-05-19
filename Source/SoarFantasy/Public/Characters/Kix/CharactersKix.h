// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/CharactersBASE.h"
#include "SystemItems/SoarFantasyInterface.h"

#include "CharactersKix.generated.h"

/**
 * 
 */
UCLASS()
class SOARFANTASY_API ACharactersKix : public ACharactersBASE, public ISoarFantasyInterface
{
	GENERATED_BODY()
	
public:
	ACharactersKix();

	virtual void Tick(float DeltaTime) override;
	void UpdateMakeCoinMovetoPlayer();
	void AddCoinScore(int32 Score);

	//Input FUNC
	virtual void Jump() override;
	virtual void Landed(const FHitResult& Hit) override;
	void Down();

	void ActiveKixsMag();

	//Visual
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
	class USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
	class UCameraComponent* MainPlatformCamera;

	//Movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump")
	bool bDoingDoubleJump = false;
	UFUNCTION(BlueprintCallable)
	void MakeStuck(bool bStuck) { bIsStuck = bStuck; }

	//Anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	class UAnimMontage* JumpMontage;

	//Score
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	float MaxCoinBarValue = 1000.f;
	int32 GetPlayerCurrentScore() const { return CurrentScore; }
	int32 GetPlayerCoinScoreScore() const { return CoinScore; }
	int32 GetPlayerPerformanceScore() const { return PerformanceScore; }
	int32 GetPlayerDistanceScore() const { return DistanceScore; }

	//DistanceScore
	FTimerHandle AddDistanceScoreHandle;

	//PauseHUD
	void OpenOrClosePauseGameMenu(bool bPauseMenuActivating);
	bool GetOtherOverlayActivating() const { return bOtherOverlayIsActivated; };

	//EndHud
	void OpenEndMenu();

	//Dead
	UFUNCTION(BlueprintCallable)
	void KixDead();

	//Level
	UPROPERTY(EditAnywhere, Category = "DataLayer")
	class UDataLayerAsset* MainLevelLayerAsset;
	UPROPERTY(EditAnywhere, Category = "DataLayer")
	class UDataLayerAsset* BonusLevelLayerAsset;

protected:
	virtual void BeginPlay() override;

	void SwitchToNormalMap();
	void SwitchToBonusMap();
	//Sound
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	class USoundBase* DeadSound;

private:
	void InitializeSFOverlay();
	//HUD
	UPROPERTY()
	class USFOverlay* SFOverlay;
	UPROPERTY()
	class UPauseOverlay* PauseOverlay;
	UPROPERTY()
	class UEndOverlay* EndOverlay;
	bool bOtherOverlayIsActivated = false;
	FTimerHandle SetBonusTimeHandle;
	bool bBonusTime = false;
	void SetBonusTimeTrue();
	void SetBonusTimeFalse();

	//Score
	float BarPercent;
	float BarCurrentScore;
	int32 CoinScore = 0;
	int32 DistanceScore = 0;
	int32 PerformanceScore = 0;
	int32 CurrentScore = 0;
	void AddDistanceScore();

	//Magnet
	FTimerHandle MagnetTimerHandle;
	bool bMagnetActive = false;
	float MagnetRadius = 500.f;
	void DeactivateKixsMag();

	//Movement
	FVector StartLocation;
	FVector CurrentLocation;
	bool bIsStuck = false;
};
