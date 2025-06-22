// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MapDataRow.generated.h"

/**
 * ================================
 * FMapDataRow
 * �ޥå������äΥǩ`���Ʃ`�֥���
 * Data table row for procedural map generation
 * ================================
 */
USTRUCT(BlueprintType)
struct SOARFANTASY_API FMapDataRow : public FTableRowBase
{
    GENERATED_BODY()

    // �ץ�åȥե��`��Υǩ`��
    // ��: "11" �� 1 ���ץ�åȥե��`�फ�� �ߤ�1.1��
    // �������ФΈ��ϡ��ץ�åȥե��`������ɤ��ʤ����������Ϻ�������ɤ��������Ԥ��꣩
    // Platform data, e.g., "11" means type 1 platform with height 1.1�� base
    // Empty means no platform (but obstacles may still spawn)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Data")
    FString Platform_Layer;

    // ���Υǩ`��
    // Enemy data
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Data")
    FString Enemy_Layer;

    // ������Υǩ`��
    // ��: "15" �� 1 �������� �� 5��
    // �������ФΈ��ϡ�����������ɤ��ʤ�
    // Coin data, e.g., "15" means type 1 coin �� 5 coins
    // Empty means no coins
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Data")
    FString Coin_Layer;

    // �����Ϻ���Υǩ`��
    // ��: "1" �� 1 �������Ϻ��������
    // λ�äϥץ�åȥե��`��θߤ�������У��ޤ��ϻ��ʸߤ�+1000�gλ
    // Air obstacle data, e.g., "1" means spawn type 1 aerial obstacle
    // Position is based on platform height (if exists) or base height + 1000 units
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Data")
    FString Air_Layer;
};
