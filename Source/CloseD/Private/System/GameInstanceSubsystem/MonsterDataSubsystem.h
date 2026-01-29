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
	TSubclassOf<AMonsterBase> MonsterClass;

	UPROPERTY(BlueprintReadOnly)
	int32 Count;
};

USTRUCT(BlueprintType)
struct FMonsterInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AMonsterBase> MonsterClass;

	UPROPERTY(EditAnywhere, Category = "Info")
	float Max_Hp;//최대 체력

	UPROPERTY(EditAnywhere, Category = "Info")
	float Attack;//공격력

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
	int32 Cost;//캐릭터 가치

	UPROPERTY(EditAnywhere)
	int32 MaxPerWave;
};

UCLASS()
class UMonsterDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	UDataTable* MonsterTable;

	ABlockGameMode* InGameMode;

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	const FMonsterInfo* GetRandomMonsterData() const;
	
	int32 GetMaxMonsterTypeForWave(int32 WaveIndex) const;

	TArray<FMonsterInWave> BuildWave(int32 WaveIndex, int32 WaveValue) const;

	const FMonsterInfo* GetRandomMonsterData(int32 RemainValue) const;
public:
	const FMonsterInfo* GetMonsterInfo(FName MonsterID) const
	{
		return MonsterTable->FindRow<FMonsterInfo>(MonsterID, TEXT("MonsterData"));
	}
};
