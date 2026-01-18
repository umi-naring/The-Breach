// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Manager/Spawner.h"

#include "Monster/MonsterBase.h"

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

void ASpawner::SpawnMonster()
{
	for (auto& Elem : MonsterInfo)
	{
		AMonsterBase* SpawnedMonster = GetWorld()->SpawnActor<AMonsterBase>(Elem.Key, this->GetActorLocation(), FRotator::ZeroRotator);
		SetMonsterInfo(SpawnedMonster, Elem.Value);
	}
}

void ASpawner::SetMonsterInfo(AMonsterBase* Spawner, FMonsterSpawningInfo& Info)
{
	Spawner->MonsterInfo.Max_Hp = Info.Max_Hp;

	Spawner->MonsterInfo.Attack = Info.Attack;
	Spawner->MonsterInfo.Defense = Info.Defense;

	Spawner->MonsterInfo.Penetration = Info.Penetration;

	Spawner->MonsterInfo.AttackDist = Info.AttackDist;
	Spawner->MonsterInfo.RecognizeDist = Info.RecognizeDist;

	Spawner->MonsterInfo.Speed = Info.Speed;
	Spawner->MonsterInfo.RunSpeed = Info.RunSpeed;
	Spawner->MonsterInfo.EXP = Info.EXP;

}