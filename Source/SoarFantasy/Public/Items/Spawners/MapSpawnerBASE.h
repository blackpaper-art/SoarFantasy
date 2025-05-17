// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapSpawnerBASE.generated.h"

UCLASS()
class SOARFANTASY_API AMapSpawnerBASE : public AActor
{
	GENERATED_BODY()
	
public:
    AMapSpawnerBASE();

protected:
    virtual void BeginPlay() override;

    // ���ݱ�ָ�룬���ڶ�ȡ��ͼ���ݣ����ڱ༭���а󶨶�Ӧ��DataTable�ʲ���
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map")
    UDataTable* MapDataTable;

    // ��������ƽ̨���ϰ���� GroundBASE ��ͼ��BP_Ground��
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
    TSubclassOf<class AGroundBASE> GroundBP;

    // ��ͼ���ɵĻ�׼λ�ã���������Ϊ������ Actor ��λ�ã�
    UPROPERTY(EditAnywhere, Category = "Map")
    FVector BaseLocation;

    // ƽ̨�ߴ磨��,��,�ߣ���ӦΪ (500, 200, 500)
    UPROPERTY(EditAnywhere, Category = "Map")
    FVector PlatformSize = FVector(200.f, 500.f, 500.f);

    // ��ƽ̨����Ϊ��ʱ�������ĺ�������ȣ�Ĭ��200��
    UPROPERTY(EditAnywhere, Category = "Map")
    float GapWidth = 200.f;

    // ���� DataTable ���ɵ�ͼ
    void GenerateMap();

public:
    virtual void Tick(float DeltaTime) override;

};
