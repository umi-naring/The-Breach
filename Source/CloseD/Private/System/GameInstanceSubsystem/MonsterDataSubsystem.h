// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MonsterDataSubsystem.generated.h"

class ABlockGameMode;
class ASpawner;
class AMonsterBase;

USTRUCT(BlueprintType)
struct FMonsterInWave
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FName MonsterID = NAME_None;

	UPROPERTY(BlueprintReadOnly)
	TSubclassOf<AMonsterBase> MonsterClass = nullptr;

	UPROPERTY(BlueprintReadOnly)
	int32 Count = 0;
};

USTRUCT(BlueprintType)
struct FMonsterInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AMonsterBase> MonsterClass = nullptr;

	UPROPERTY(EditAnywhere, Category = "Info")
	float Max_Hp = 100.f;//최대 체력

	UPROPERTY(EditAnywhere, Category = "Info")
	float Attack = 10.f;//공격력

	UPROPERTY(EditAnywhere, Category = "Info")
	float Defense;//방어력

	UPROPERTY(EditAnywhere, Category = "Info")
	float Penetration;//방어력 관통

	UPROPERTY(EditAnywhere, Category = "Info")
	float AttackDist;//공격 사거리

	UPROPERTY(EditAnywhere, Category = "Info")
	float RecognizeDist;//인식 사거리

	UPROPERTY(EditAnywhere, Category = "Info")
	float Speed;//속도

	UPROPERTY(EditAnywhere, Category = "Info")
	float RunSpeed;//달리는 속도

	UPROPERTY(EditAnywhere, Category = "Info")
	float EXP;//죽인 말한테 들어가는 경험치

	UPROPERTY(EditAnywhere, Category = "Info")
	int32 Value;//캐릭터 가치

	UPROPERTY(EditAnywhere)
	int32 MaxPerWave;
};

USTRUCT(BlueprintType)
struct FWaveInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<AMonsterBase>> AllowedMonster;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxMonsterTypes = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ValueMultiplier = 1.f;
};

UCLASS(Config=Game, DefaultConfig)
class UMonsterDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Config)
	TSoftObjectPtr<UDataTable> MonsterTable;

	UPROPERTY(EditDefaultsOnly, Config)
	TSoftObjectPtr<UDataTable> WaveTable;

	UPROPERTY(EditDefaultsOnly, Config)
	float AutoValueGrowth = 1.15f;

	UPROPERTY(EditDefaultsOnly, Config)
	int32 AutoMaxTypesPerWave = 3;

	UPROPERTY(EditDefaultsOnly, Config)
	int32 MaxMonsterTypesCap = 5;

	UPROPERTY(Transient)
	UDataTable* LoadedMonsterTable = nullptr;

	UPROPERTY(Transient)
	UDataTable* LoadedWaveTable = nullptr;

	ABlockGameMode* InGameMode;

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	const FMonsterInfo* GetRandomMonsterData() const;
	const FMonsterInfo* GetRandomMonsterData(int32 RemainValue, FName& OutMonsterID) const;
	const FMonsterInfo* GetRandomMonsterDataFromList(int32 RemainValue, const TArray<TSubclassOf<AMonsterBase>>& Candidates, FName& OutMonsterID) const;

	int32 GetMaxMonsterTypeForWave(int32 WaveIndex) const;
	float GetWaveValueMultiplier(int32 WaveIndex) const;
	int32 GetExplicitWaveCount() const;
	const FWaveInfo* GetWaveRule(int32 WaveIndex) const;
	const FWaveInfo* GetLastWaveRule() const;

	TArray<FMonsterInWave> BuildWave(int32 WaveIndex, int32 WaveValue) const;

public:
	const FMonsterInfo* GetMonsterInfo(FName MonsterID) const
	{
		return LoadedMonsterTable
			? LoadedMonsterTable->FindRow<FMonsterInfo>(MonsterID, TEXT("MonsterData"))
			: nullptr;
	}

	TArray<FMonsterInWave> BuildWaveData(int32 WaveIndex, int32 WaveValue) const
	{
		return BuildWave(WaveIndex, WaveValue);
	}
};
