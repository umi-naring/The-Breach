// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UnitDataSubsystem.generated.h"

class AUnitBase;

USTRUCT(BlueprintType)
struct FUnitInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AUnitBase> UnitClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	int32 LV = 1;//최대 체력

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	float Max_Hp = 100.f;//최대 체력

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	float Attack = 10.f;//공격력

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	float Defense = 5.f;//방어력

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	float Penetration = 10.f;//방어력 관통

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	float AttackDist = 150.f;//공격 사거리

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	float RecognizeDist = 300.f;//인식 사거리

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	float Speed = 600.f;//속도

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	float RunSpeed = 800.f;//달리는 속도

	UPROPERTY()
	float Current_EXP = 0;//죽인 말한테 들어가는 경험치

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	float Max_EXP = 30.f;//죽인 말한테 들어가는 경험치

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	int32 Value = 2;//캐릭터 가치
};

UCLASS(Config=Game, DefaultConfig)
class UUnitDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Config)
	TSoftObjectPtr<UDataTable> UnitTable;

	UPROPERTY(Transient)
	UDataTable* LoadedUnitTable = nullptr;

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	const FUnitInfo* GetUnitInfo(FName UnitID) const
	{
		return LoadedUnitTable
			? LoadedUnitTable->FindRow<FUnitInfo>(UnitID, TEXT("UnitData"))
			: nullptr;
	}
};
