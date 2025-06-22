// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SoarFantasyInterface.generated.h"

/**
 * ====================================
 * USoarFantasyInterface
 * SoarFantasy�äι�ͨ���󥿩`�ե��`��
 * Common interface for SoarFantasy objects
 * ====================================
 */
UINTERFACE(MinimalAPI)
class USoarFantasyInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * ====================================
 * ISoarFantasyInterface
 * ���Υ��󥿩`�ե��`����@�Ф��륯�饹���gװ����C��
 * Functions that inheriting classes should implement
 * ====================================
 */
class SOARFANTASY_API ISoarFantasyInterface
{
    GENERATED_BODY()

public:
    // �����󥹥�������㤹�빲ͨ�v��
    // Add coin score function (to be overridden)
    virtual void AddCoinScore(int32 Score);
};
