// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "System/BlockGameMode.h"
#include "System/GameInstanceSubsystem/MonsterDataSubsystem.h"
#include "Spawner.generated.h"

class AMonsterBase;
class UMonsterManagerComponent;
class UMonsterDataSubsystem;

UCLASS()
class ASpawner : public AActor
{
	GENERATED_BODY()
private:
	UMonsterManagerComponent* MonsterManager;
	ABlockGameMode* InGameMode;
	UMonsterDataSubsystem* MonsterData = nullptr;

	FTimerHandle SpawnTimer;
	TArray<FMonsterInWave> PendingWave;
	int32 PendingWaveIndex = 0;
	int32 PendingRemainCount = 0;
	int32 AliveCount = 0;

	bool bIsSpawning = false;

private:
	void GetGameMode() { InGameMode = Cast<ABlockGameMode>(GetWorld()->GetAuthGameMode()); }
	void CacheSubsystems();
	void StartSpawnTimer();
	void StopSpawnTimer();
	void SpawnTick();
	bool TrySpawnOne();
	bool SpawnMonsterInternal(FName MonsterID);

	UFUNCTION()
	void OnMonsterDestroyed(AActor* DestroyedActor);

public:	
	ASpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	bool bAutoStart = false;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	int32 AutoStartWaveIndex = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	int32 AutoStartWaveValue = 10;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	float SpawnInterval = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	int32 SpawnBatchSize = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	int32 MaxAliveMonsters = 30;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	float SpawnRadius = 0.f;

	UFUNCTION(BlueprintCallable)
	bool StartWave(int32 WaveIndex, int32 WaveValue);

	UFUNCTION(BlueprintCallable)
	void StopWave();

	UFUNCTION(BlueprintCallable)
	bool IsSpawning() const { return bIsSpawning; }

	void SpawnMonster(FName MonsterID);
};
