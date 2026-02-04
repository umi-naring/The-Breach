// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Monster/Manager/Spawner.h"

#include "Character/Monster/MonsterBase.h"
#include "System/GameInstanceSubsystem/MonsterDataSubsystem.h"

// Sets default values
ASpawner::ASpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();

	GetGameMode();
	CacheSubsystems();

	if (bAutoStart)
		StartWave(AutoStartWaveIndex, AutoStartWaveValue);
}

void ASpawner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	StopSpawnTimer();
	Super::EndPlay(EndPlayReason);
}

void ASpawner::CacheSubsystems()
{
	MonsterData = nullptr;

	if (!GetGameInstance())
		return;

	MonsterData = GetGameInstance()->GetSubsystem<UMonsterDataSubsystem>();
}

bool ASpawner::StartWave(int32 WaveIndex, int32 WaveValue)
{
	if (bIsSpawning)
		return false;

	if (!MonsterData)
		CacheSubsystems();

	if (!MonsterData || WaveValue <= 0)
		return false;

	PendingWave = MonsterData->BuildWaveData(WaveIndex, WaveValue);
	if (PendingWave.Num() == 0)
		return false;

	PendingWaveIndex = 0;
	PendingRemainCount = PendingWave[PendingWaveIndex].Count;

	bIsSpawning = true;
	StartSpawnTimer();
	return true;
}

void ASpawner::StopWave()
{
	StopSpawnTimer();
	bIsSpawning = false;
	PendingWave.Empty();
	PendingWaveIndex = 0;
	PendingRemainCount = 0;
}

void ASpawner::StartSpawnTimer()
{
	if (!GetWorld())
		return;

	GetWorld()->GetTimerManager().SetTimer(
		SpawnTimer,
		this,
		&ASpawner::SpawnTick,
		SpawnInterval,
		true
	);
}

void ASpawner::StopSpawnTimer()
{
	if (!GetWorld())
		return;

	GetWorld()->GetTimerManager().ClearTimer(SpawnTimer);
}

void ASpawner::SpawnTick()
{
	if (!bIsSpawning)
		return;

	if (AliveCount >= MaxAliveMonsters)
		return;

	bool bSpawnedAny = false;

	for (int i = 0; i < SpawnBatchSize; ++i)
	{
		if (AliveCount >= MaxAliveMonsters)
			break;

		if (!TrySpawnOne())
			break;

		bSpawnedAny = true;
	}

	if (!bSpawnedAny && PendingWaveIndex >= PendingWave.Num())
		StopWave();
}

bool ASpawner::TrySpawnOne()
{
	if (PendingWaveIndex >= PendingWave.Num())
		return false;

	if (PendingRemainCount <= 0)
	{
		PendingRemainCount = PendingWave[PendingWaveIndex].Count;

		if (PendingRemainCount <= 0)
		{
			++PendingWaveIndex;
			return true;
		}
	}

	if (!SpawnMonsterInternal(PendingWave[PendingWaveIndex].MonsterID))
	{
		PendingRemainCount = 0;
		++PendingWaveIndex;
		return true;
	}

	--PendingRemainCount;

	if (PendingRemainCount <= 0)
	{
		++PendingWaveIndex;

		if (PendingWaveIndex < PendingWave.Num())
			PendingRemainCount = PendingWave[PendingWaveIndex].Count;
	}

	return true;
}

void ASpawner::SpawnMonster(FName MonsterID)
{
	SpawnMonsterInternal(MonsterID);
}

bool ASpawner::SpawnMonsterInternal(FName MonsterID)
{
	if (!MonsterData || !GetWorld() || MonsterID.IsNone())
		return false;

	const FMonsterInfo* Data = MonsterData->GetMonsterInfo(MonsterID);
	if (!Data || !Data->MonsterClass)
		return false;

	FTransform SpawnTransform = GetActorTransform();

	if (SpawnRadius > 0.f)
	{
		const float Angle = FMath::FRandRange(0.f, 2.f * PI);
		const float Radius = FMath::Sqrt(FMath::FRand()) * SpawnRadius;
		const FVector Offset(
			FMath::Cos(Angle) * Radius,
			FMath::Sin(Angle) * Radius,
			0.f
		);

		SpawnTransform.AddToTranslation(Offset);
	}

	AMonsterBase* Monster = GetWorld()->SpawnActorDeferred<AMonsterBase>(
		Data->MonsterClass,
		SpawnTransform,
		this,
		nullptr,
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn
	);

	if (!Monster)
		return false;

	Monster->MonsterInfo = *Data;

	Monster->InitInfo(EStatsType::HP, Data->Max_Hp);
	Monster->InitInfo(EStatsType::ATTACK, Data->Attack);
	Monster->InitInfo(EStatsType::DEFENSE, Data->Defense);
	Monster->InitInfo(EStatsType::PENETRATION, Data->Penetration);
	Monster->InitInfo(EStatsType::ATTACK_DIST, Data->AttackDist);
	Monster->InitInfo(EStatsType::RECOGNIZE_DIST, Data->RecognizeDist);
	Monster->InitInfo(EStatsType::SPEED, Data->Speed);
	Monster->InitInfo(EStatsType::RUNSPEED, Data->RunSpeed);

	Monster->OnDestroyed.AddDynamic(this, &ASpawner::OnMonsterDestroyed);
	Monster->FinishSpawning(SpawnTransform);

	++AliveCount;
	return true;
}

void ASpawner::OnMonsterDestroyed(AActor* DestroyedActor)
{
	if (AliveCount > 0)
		--AliveCount;
}