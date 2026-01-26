// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "System/BlockGameMode.h"
#include "Spawner.generated.h"

class AMonsterBase;
class UMonsterManagerComponent;

UCLASS()
class ASpawner : public AActor
{
	GENERATED_BODY()
private:
	UMonsterManagerComponent* MonsterManager;
	ABlockGameMode* InGameMode;


private:
	void GetGameMode() { InGameMode = Cast<ABlockGameMode>(GetWorld()->GetAuthGameMode()); }
	void SetMonsterManager() { MonsterManager = InGameMode->GetMonsterManagerComponent(); };
	void BuildWave(int WaveValue);

	//void SetMonsterInfo(AMonsterBase* Spawner, FMonsterSpawningInfo& Info);

public:	
	ASpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SpawnMonster(FName MonsterID);
};
