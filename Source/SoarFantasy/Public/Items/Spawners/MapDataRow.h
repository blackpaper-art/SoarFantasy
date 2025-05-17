// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MapDataRow.generated.h"

USTRUCT(BlueprintType)
struct SOARFANTASY_API FMapDataRow : public FTableRowBase
{
    GENERATED_BODY()

    // ƽ̨���ݣ����� "11" ��ʾ1����ʽƽ̨�Ҹ߶�Ϊ�����߶ȵ�1.1����
    // �������ʾ�˵�ͼ��Ԫ������ƽ̨���������ϰ�����Ȼ�������ɣ�
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Data")
    FString Platform_Layer;

    //Enemy Layer
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Data")
    FString Enemy_Layer;

    // ������ݣ����� "15" ��ʾʹ��1�Ž����ʽ����5����ң�
    // �������ʾ��ƽ̨�ϲ����ɽ��
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Data")
    FString Coin_Layer;

    // �����ϰ������ݣ����� "1" ��ʾ����1�����͵��ϰ��
    // ����λ�û���ƽ̨�߶ȣ���ƽ̨���ڣ�������߶ȼ� 1000��λ
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Data")
    FString Air_Layer;
};
