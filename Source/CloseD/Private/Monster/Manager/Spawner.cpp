// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Manager/Spawner.h"

#include "Monster/MonsterBase.h"
#include "Monster/Manager/MonsterManagerComponent.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();

	GetGameMode();
	SetMonsterManager();
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawner::SpawnMonster(FName MonsterID)
{
	/*const FMonsterInfo* Data = MonsterData->GetMonsterInfo(MonsterID);
	if (!Data) return;

	AMonsterBase* Monster = GetWorld()->SpawnActor<AMonsterBase>(MonsterClass, GetActorTransform());*/

	/*Monster->InitInfo(EStatsType::HP, Data->Max_Hp);
	Monster->InitInfo(EStatsType::ATTACK, Data->Attack);
	Monster->InitInfo(EStatsType::SPEED, Data->Speed);
	Monster->InitInfo(EStatsType::ATTACK_DIST, Data->AttackDist);*/
}

void ASpawner::BuildWave(int WaveValue)
{
	/*int RemainValue = WaveValue;

	TArray<FMonsterWaveUnit> Result;

	for (int i = 0; i < MaxMonsterTypePerWave; ++i)
	{
		const FMonsterInfo* Data = GetRandomMonsterData();
		if (!Data) break;

		int MaxSpawn = FMath::Min(
			Data->MaxPerWave,
			RemainValue / Data->Cost
		);

		if (MaxSpawn <= 0)
			continue;

		int SpawnCount = FMath::RandRange(1, MaxSpawn);

		Result.Add({ Data->RowName, SpawnCount });
		RemainValue -= SpawnCount * Data->Cost;

		if (RemainValue <= 0)
			break;
	}*/
}
//void ASpawner::SetMonsterInfo(AMonsterBase* Spawner, FMonsterSpawningInfo& Info)
//{
//	Spawner->MonsterInfo.Max_Hp = Info.Max_Hp;
//
//	Spawner->MonsterInfo.Attack = Info.Attack;
//	Spawner->MonsterInfo.Defense = Info.Defense;
//
//	Spawner->MonsterInfo.Penetration = Info.Penetration;
//
//	Spawner->MonsterInfo.AttackDist = Info.AttackDist;
//	Spawner->MonsterInfo.RecognizeDist = Info.RecognizeDist;
//
//	Spawner->MonsterInfo.Speed = Info.Speed;
//	Spawner->MonsterInfo.RunSpeed = Info.RunSpeed;
//	Spawner->MonsterInfo.EXP = Info.EXP;
//
//}