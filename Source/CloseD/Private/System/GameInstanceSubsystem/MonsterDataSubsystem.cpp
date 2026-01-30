// Fill out your copyright notice in the Description page of Project Settings.


#include "System/GameInstanceSubsystem/MonsterDataSubsystem.h"

#include "Character/Monster/Manager/Spawner.h"
#include "Character/Monster/MonsterBase.h"

void UMonsterDataSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UMonsterDataSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

TArray<FMonsterInWave> UMonsterDataSubsystem::BuildWave(int32 WaveIndex, int32 WaveValue) const
{
	int32 RemainValue = WaveValue;
	TArray<FMonsterInWave> Result;

	int32 MaxTypes = GetMaxMonsterTypeForWave(WaveIndex);

	for (int i = 0; i < MaxTypes; ++i)
	{
		const FMonsterInfo* Data = GetRandomMonsterData(RemainValue);
		if (!Data)
			break;

		int32 MaxSpawn = FMath::Min(
			Data->MaxPerWave,
			RemainValue / Data->Cost
		);

		if (MaxSpawn <= 0)
			continue;

		int32 SpawnCount = FMath::RandRange(1, MaxSpawn);

		Result.Add({ Data->MonsterClass, SpawnCount });
		RemainValue -= SpawnCount * Data->Cost;

		if (RemainValue <= 0)
			break;
	}

	return Result;
}

const FMonsterInfo* UMonsterDataSubsystem::GetRandomMonsterData(int32 RemainValue) const
{
	if (MonsterTable == nullptr)
		return nullptr;

	TArray<FName> RowNames = MonsterTable->GetRowNames();
	if (RowNames.Num() == 0)
		return nullptr;

	int Index = FMath::RandRange(0, RowNames.Num() - 1);

	return MonsterTable->FindRow<FMonsterInfo>(
		RowNames[Index],
		TEXT("GetRandomMonsterData")
	);
}

int32 UMonsterDataSubsystem::GetMaxMonsterTypeForWave(int32 WaveIndex) const
{
	if (WaveIndex < 3) 
		return 1;
	else if (WaveIndex < 7)
		return 2;
	else if (WaveIndex < 12) 
		return 3;
	else 
		return 4;
}


