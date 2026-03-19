// Fill out your copyright notice in the Description page of Project Settings.


#include "System/GameInstanceSubsystem/MonsterDataSubsystem.h"

#include "Character/Monster/Manager/Spawner.h"
#include "Character/Monster/MonsterBase.h"

void UMonsterDataSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// 몬스터 데이터 테이블 로드
	LoadedMonsterTable = MonsterTable.IsNull()
		? nullptr
		: MonsterTable.LoadSynchronous();

	// 웨이브 규칙 테이블 로드		
	LoadedWaveTable = WaveTable.IsNull()
		? nullptr
		: WaveTable.LoadSynchronous();
}

void UMonsterDataSubsystem::Deinitialize()
{
	LoadedMonsterTable = nullptr;
	LoadedWaveTable = nullptr;
	Super::Deinitialize();
}

TArray<FMonsterInWave> UMonsterDataSubsystem::BuildWave(int32 WaveIndex, int32 WaveValue) const
{
	const float ValueMultiplier = GetWaveValueMultiplier(WaveIndex);
	int32 RemainValue = FMath::RoundToInt(WaveValue * ValueMultiplier);// 남은 가치 포인트
	TArray<FMonsterInWave> Result;// 이번 웨이브에 포함될 몬스터 정보 배열

	const FWaveInfo* Rule = GetWaveRule(WaveIndex);
	const FWaveInfo* FallbackRule = Rule ? Rule : GetLastWaveRule();
	const TArray<TSubclassOf<AMonsterBase>>* AllowedList = (FallbackRule && FallbackRule->AllowedMonster.Num() > 0)
		? &FallbackRule->AllowedMonster
		: nullptr;

	int32 MaxTypes = GetMaxMonsterTypeForWave(WaveIndex);// 웨이브에 등장할 수 있는 몬스터 종류의 최대 개수

	TArray<TSubclassOf<AMonsterBase>> WaveCandidates;
	if (AllowedList)
	{
		WaveCandidates = *AllowedList;
	}
	else if (LoadedMonsterTable)
	{
		const TArray<FName> RowNames = LoadedMonsterTable->GetRowNames();
		WaveCandidates.Reserve(RowNames.Num());
		for (const FName& RowName : RowNames)
		{
			if (const FMonsterInfo* Data = LoadedMonsterTable->FindRow<FMonsterInfo>(RowName, TEXT("BuildWave_Candidates")))
				WaveCandidates.Add(Data->MonsterClass);
		}
	}

	if (WaveCandidates.Num() > MaxTypes)
	{
		TArray<TSubclassOf<AMonsterBase>> Temp = WaveCandidates;
		WaveCandidates.Reset(MaxTypes);
		for (int32 i = 0; i < MaxTypes && Temp.Num() > 0; ++i)
		{
			const int32 Index = FMath::RandRange(0, Temp.Num() - 1);
			WaveCandidates.Add(Temp[Index]);
			Temp.RemoveAtSwap(Index);
		}
	}

	TArray<TSubclassOf<AMonsterBase>> RemainingClasses = WaveCandidates;
	TSet<TSubclassOf<AMonsterBase>> UsedClasses;

	auto GetCurrentCount = [&Result](FName MonsterID)
	{
		const int32 Index = Result.IndexOfByPredicate([&](const FMonsterInWave& Entry)
		{
			return Entry.MonsterID == MonsterID;
		});
		return Index != INDEX_NONE ? Result[Index].Count : 0;
	};

	auto AddSpawn = [&Result](FName MonsterID, TSubclassOf<AMonsterBase> MonsterClass, int32 Count)
	{
		const int32 Index = Result.IndexOfByPredicate([&](const FMonsterInWave& Entry)
		{
			return Entry.MonsterID == MonsterID;
		});
		if (Index != INDEX_NONE)
			Result[Index].Count += Count;
		else
			Result.Add({ MonsterID, MonsterClass, Count });
	};

	for (int i = 0; i < MaxTypes && RemainingClasses.Num() > 0 && RemainValue > 0; ++i)
	{
		FName MonsterID;// 랜덤으로 선택된 몬스터 ID를 저장할 변수

		const FMonsterInfo* Data = RemainingClasses.Num() > 0
			? GetRandomMonsterDataFromList(RemainValue, RemainingClasses, MonsterID)
			: nullptr;// 남은 가치 포인트를 기반으로 랜덤하게 몬스터 데이터를 가져옴
		if (!Data || Data->Value <= 0)
			break;

		RemainingClasses.Remove(Data->MonsterClass);

		const int32 ExistingCount = GetCurrentCount(MonsterID);
		int32 MaxAllowed = Data->MaxPerWave > 0 ? FMath::Max(0, Data->MaxPerWave - ExistingCount) : 0;
		int32 MaxSpawn = FMath::Min(MaxAllowed, RemainValue / Data->Value);// 해당 몬스터의 최대 스폰 가능 수를 계산 (남은 가치 포인트와 몬스터의 가치에 따라 결정)

		if (MaxSpawn <= 0)
			continue;

		int32 SpawnCount = FMath::RandRange(1, MaxSpawn);//	1부터 최대 스폰 가능 수 사이에서 랜덤하게 스폰할 몬스터 수를 결정

		AddSpawn(MonsterID, Data->MonsterClass, SpawnCount);// 결정된 몬스터 ID, 클래스, 수량을 결과 배열에 추가
		UsedClasses.Add(Data->MonsterClass);
		RemainValue -= SpawnCount * Data->Value;// 스폰한 몬스터들의 가치만큼 남은 가치 포인트에서 차감

		if (RemainValue <= 0)
			break;
	}

	while (RemainValue > 0 && LoadedMonsterTable)
	{
		const bool bAllowNewTypes = UsedClasses.Num() < MaxTypes;
		const TArray<FName> RowNames = LoadedMonsterTable->GetRowNames();
		const FMonsterInfo* BestData = nullptr;
		FName BestID = NAME_None;

		for (const FName& RowName : RowNames)
		{
			const FMonsterInfo* Data = LoadedMonsterTable->FindRow<FMonsterInfo>(RowName, TEXT("BuildWave_Fill"));
			if (!Data || Data->Value <= 0 || Data->Value > RemainValue)
				continue;

			const bool bIsAllowed = bAllowNewTypes
				? WaveCandidates.Contains(Data->MonsterClass)
				: UsedClasses.Contains(Data->MonsterClass);
			if (!bIsAllowed)
				continue;

			const int32 ExistingCount = GetCurrentCount(RowName);
			const int32 MaxAllowed = Data->MaxPerWave > 0 ? Data->MaxPerWave - ExistingCount : 0;
			if (MaxAllowed <= 0)
				continue;

			if (!BestData || Data->Value < BestData->Value)
			{
				BestData = Data;
				BestID = RowName;
			}
		}

		if (!BestData)
			break;

		const int32 ExistingCount = GetCurrentCount(BestID);
		const int32 MaxAllowed = BestData->MaxPerWave > 0 ? BestData->MaxPerWave - ExistingCount : 0;
		const int32 SpawnCount = FMath::Min(MaxAllowed, RemainValue / BestData->Value);
		if (SpawnCount <= 0)
			break;

		AddSpawn(BestID, BestData->MonsterClass, SpawnCount);
		UsedClasses.Add(BestData->MonsterClass);
		RemainValue -= SpawnCount * BestData->Value;
	}

	return Result;
}

const FMonsterInfo* UMonsterDataSubsystem::GetRandomMonsterData(int32 RemainValue, FName& OutMonsterID) const
{
	if (LoadedMonsterTable == nullptr)
		return nullptr;

	TArray<FName> RowNames = LoadedMonsterTable->GetRowNames();
	if (RowNames.Num() == 0)
		return nullptr;

	TArray<TSubclassOf<AMonsterBase>> Candidates;
	Candidates.Reserve(RowNames.Num());

	for (const FName& RowName : RowNames)
	{
		if (const FMonsterInfo* Data = LoadedMonsterTable->FindRow<FMonsterInfo>(RowName, TEXT("GetRandomMonsterData_All")))
			Candidates.Add(Data->MonsterClass);
	}

	return GetRandomMonsterDataFromList(RemainValue, Candidates, OutMonsterID);
}

const FMonsterInfo* UMonsterDataSubsystem::GetRandomMonsterDataFromList(int32 RemainValue, const TArray<TSubclassOf<AMonsterBase>>& Candidates, FName& OutMonsterID) const
{
	if (LoadedMonsterTable == nullptr)
		return nullptr;

	TArray<FName> ValidRows;
	ValidRows.Reserve(Candidates.Num());

	const TArray<FName> RowNames = LoadedMonsterTable->GetRowNames();

	for (const FName& RowName : RowNames)
	{
		const FMonsterInfo* Data = LoadedMonsterTable->FindRow<FMonsterInfo>(
			RowName,
			TEXT("GetRandomMonsterData_Filter")
		);

		if (!Data)
			continue;

		if (!Candidates.Contains(Data->MonsterClass))
			continue;

		if (Data->Value <= RemainValue)
			ValidRows.Add(RowName);
	}

	if (ValidRows.Num() == 0)
		return nullptr;

	int32 Index = FMath::RandRange(0, ValidRows.Num() - 1);
	OutMonsterID = ValidRows[Index];

	return LoadedMonsterTable->FindRow<FMonsterInfo>(
		OutMonsterID,
		TEXT("GetRandomMonsterData_Select")
	);
}

const FWaveInfo* UMonsterDataSubsystem::GetWaveRule(int32 WaveIndex) const
{
	if (!LoadedWaveTable)
		return nullptr;

	const FName NumericName(*FString::FromInt(WaveIndex));
	if (const FWaveInfo* Rule = LoadedWaveTable->FindRow<FWaveInfo>(NumericName, TEXT("GetWaveRule")))
		return Rule;

	const FName WaveName(*FString::Printf(TEXT("Wave_%d"), WaveIndex));
	return LoadedWaveTable->FindRow<FWaveInfo>(WaveName, TEXT("GetWaveRule"));
}

int32 UMonsterDataSubsystem::GetExplicitWaveCount() const
{
	return LoadedWaveTable ? LoadedWaveTable->GetRowNames().Num() : 0;
}

float UMonsterDataSubsystem::GetWaveValueMultiplier(int32 WaveIndex) const
{
	if (const FWaveInfo* Rule = GetWaveRule(WaveIndex))
		return FMath::Max(0.f, Rule->ValueMultiplier);

	const int32 ExplicitCount = GetExplicitWaveCount();
	const int32 AutoIndex = FMath::Max(0, WaveIndex - ExplicitCount);
	return FMath::Pow(AutoValueGrowth, AutoIndex);
}

int32 UMonsterDataSubsystem::GetMaxMonsterTypeForWave(int32 WaveIndex) const
{
	int32 MaxTypes = AutoMaxTypesPerWave;

	if (const FWaveInfo* Rule = GetWaveRule(WaveIndex))
		MaxTypes = Rule->MaxMonsterTypes > 0 ? Rule->MaxMonsterTypes : AutoMaxTypesPerWave;

	if (MaxMonsterTypesCap > 0)
		MaxTypes = FMath::Min(MaxTypes, MaxMonsterTypesCap);

	return FMath::Max(1, MaxTypes);
}

const FWaveInfo* UMonsterDataSubsystem::GetLastWaveRule() const
{
	if (!LoadedWaveTable)
		return nullptr;

	const TArray<FName> RowNames = LoadedWaveTable->GetRowNames();
	if (RowNames.Num() == 0)
		return nullptr;

	int32 BestIndex = -1;
	const FWaveInfo* BestRule = nullptr;

	for (const FName& RowName : RowNames)
	{
		int32 ParsedIndex = -1;
		const FString NameStr = RowName.ToString();
		if (!LexTryParseString(ParsedIndex, *NameStr))
		{
			const FString Prefix = TEXT("Wave_");
			if (NameStr.StartsWith(Prefix))
				LexTryParseString(ParsedIndex, *NameStr.Mid(Prefix.Len()));
		}

		if (ParsedIndex < 0)
			continue;

		if (ParsedIndex > BestIndex)
		{
			if (const FWaveInfo* Rule = LoadedWaveTable->FindRow<FWaveInfo>(RowName, TEXT("GetLastWaveRule")))
			{
				BestIndex = ParsedIndex;
				BestRule = Rule;
			}
		}
	}

	return BestRule;
}