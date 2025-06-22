// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "KixPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class ACharactersKix;

/**
 * ====================================
 * AKixPlayerController
 * �ץ쥤��`����������륳��ȥ�`��
 * Player controller for handling player input
 * ====================================
 */

 // �ݩ`����˥�`״�B���В���
 // Enum for pause menu UI state
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
    // ��������ݩ`�ͥ�Ȥ򥻥åȥ��å�
    // Setup input component bindings
    virtual void SetupInputComponent() override;

    // �F��ʹ�ä��� Input Mapping Context
    // Current input mapping context
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    TObjectPtr<UInputMappingContext> CurrentMappingContext;

    // �����ץ��������
    // Jump action
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    TObjectPtr<UInputAction> JumpAction;

    // ���㤬�ॢ�������
    // Down action
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    TObjectPtr<UInputAction> DownAction;

    // ���å��奢�������
    // Dash action
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    TObjectPtr<UInputAction> DashAction;

    // �ݩ`�����������
    // Pause action
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    TObjectPtr<UInputAction> PauseAction;

    // �F�ڲ������Ƥ��륭��饯���`
    // Currently possessed character
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    TObjectPtr<ACharactersKix> CurrentChara;

    // �ݩ`��״�B����ڻ�
    // Reset pause flags
    void SetPauseBoolFalse();

    // �F�ڤΥݩ`����˥�`״�B
    // Current pause menu UI state
    EPauseUIState CurrentPauseUIState = EPauseUIState::None;

protected:
    // �ݩ`�����Еr�˺��Ф��
    // Called when possessing a pawn
    virtual void OnPossess(APawn* InPawn) override;

    // �����ׄI��
    // Handle jump input
    void Jump();

    // �ݩ`���I��
    // Handle pause input
    void PauseGame();

    // ���㤬���I��
    // Handle down input
    void Down();

    // ���å���I��
    // Handle dash input
    void Dash();

private:
    // �ݩ`����˥�`�������ƥ��֤��ɤ���
    // Whether pause menu is active
    bool bPauseMenuActivating = false;
};
