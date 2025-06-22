// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/CharactersBASE.h"
#include "SystemItems/SoarFantasyInterface.h"

#include "CharactersKix.generated.h"

/**
 * ====================================
 * ACharactersKix
 * �ץ쥤��`����饯���`�Υᥤ�󥯥饹
 * Main player character class for SoarFantasy
 * ====================================
 */
UCLASS()
class SOARFANTASY_API ACharactersKix : public ACharactersBASE, public ISoarFantasyInterface
{
    GENERATED_BODY()

public:
    // ���󥹥ȥ饯��
    // Constructor
    ACharactersKix();

    // ���ե�`�����
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // ������Υޥ��ͥåȄI������
    // Update coin magnet effect
    void UpdateMakeCoinMovetoPlayer();

    // �����󥹥��������
    // Add coin score
    void AddCoinScore(int32 Score);

    // ����: ������
    // Input: Jump
    virtual void Jump() override;

    // �ŵؕr�΄I��
    // Called on landing
    virtual void Landed(const FHitResult& Hit) override;

    // ����: ������
    // Input: Down
    void Down();

    // ����: ���å��壨δ�gװ��
    // Input: Dash (placeholder)
    void Dash();

    // �ޥ��ͥåȤ��Є���
    // Activate magnet power-up
    void ActiveKixsMag();

    // �ӥ��奢��: ������v�B
    // Visual: Camera and spring arm
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
    class USpringArmComponent* SpringArm;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
    class UCameraComponent* MainPlatformCamera;

    // �Ӥ��v�B: ���֥른����
    // Movement: Double jump flag
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump")
    bool bDoingDoubleJump = false;

    UFUNCTION(BlueprintCallable)
    void MakeStuck(bool bStuck) { bIsStuck = bStuck; }

    // ���˥�`�����
    // Animation
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
    class UAnimMontage* JumpMontage;

    // ������ϵ
    // Scoring
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
    float MaxCoinBarValue = 1000.f;

    int32 GetPlayerCurrentScore() const { return CurrentScore; }
    int32 GetPlayerCoinScoreScore() const { return CoinScore; }
    int32 GetPlayerPerformanceScore() const { return PerformanceScore; }
    int32 GetPlayerDistanceScore() const { return DistanceScore; }

    // ���x�����������å����ީ`
    // Timer handle for distance scoring
    FTimerHandle AddDistanceScoreHandle;

    // �ݩ`����˥�`���_�]
    // Open/close pause menu
    void OpenOrClosePauseGameMenu(bool bPauseMenuActivating);

    bool GetOtherOverlayActivating() const { return bOtherOverlayIsActivated; };

    // ����ɥ�˥�`���_��
    // Open end menu
    void OpenEndMenu();

    // �����r�I��
    // Called when player dies
    UFUNCTION(BlueprintCallable)
    void KixDead();

    // �ǩ`���쥤��`
    // Level data layers
    UPROPERTY(EditAnywhere, Category = "DataLayer")
    class UDataLayerAsset* MainLevelLayerAsset;

    UPROPERTY(EditAnywhere, Category = "DataLayer")
    class UDataLayerAsset* BonusLevelLayerAsset;

protected:
    virtual void BeginPlay() override;

    // �ǩ`���쥤��`����
    void SwitchToNormalMap();
    void SwitchToBonusMap();

    // �����r��
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    class USoundBase* DeadSound;

private:
    // HUD���ڻ�
    void InitializeSFOverlay();

    // HUD���`�Щ`�쥤
    UPROPERTY()
    class USFOverlay* SFOverlay;

    UPROPERTY()
    class UPauseOverlay* PauseOverlay;

    UPROPERTY()
    class UEndOverlay* EndOverlay;

    bool bOtherOverlayIsActivated = false;

    // �ܩ`�ʥ������ީ`
    FTimerHandle SetBonusTimeHandle;
    bool bBonusTime = false;

    void SetBonusTimeTrue();
    void SetBonusTimeFalse();

    // �������ڲ�����
    float BarPercent;
    float BarCurrentScore;
    int32 CoinScore = 0;
    int32 DistanceScore = 0;
    int32 PerformanceScore = 0;
    int32 CurrentScore = 0;

    void AddDistanceScore();

    // �ޥ��ͥå�
    FTimerHandle MagnetTimerHandle;
    bool bMagnetActive = false;
    float MagnetRadius = 500.f;
    void DeactivateKixsMag();

    // �Ӥ�
    FVector StartLocation;
    FVector CurrentLocation;
    bool bIsStuck = false;
    bool bIsDash = false;
};
