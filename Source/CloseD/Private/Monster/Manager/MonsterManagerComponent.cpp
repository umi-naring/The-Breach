// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Manager/MonsterManagerComponent.h"

#include "Monster/Manager/MonsterManagerComponent.h"
#include "Monster/MonsterBase.h"
#include "Monster/Manager/Spawner.h"

// Sets default values for this component's properties
UMonsterManagerComponent::UMonsterManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMonsterManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMonsterManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMonsterManagerComponent::SetSpawnerInfo(ASpawner* Spawner, FMonsterSpawnInfo& Info)
{
	Spawner->MInfo.Max_Hp = Info.Max_Hp;

	Spawner->MInfo.Attack = Info.Attack;
	Spawner->MInfo.Defense = Info.Defense;

	Spawner->MInfo.Penetration = Info.Penetration;

	Spawner->MInfo.AttackDist = Info.AttackDist;
	Spawner->MInfo.RecognizeDist = Info.RecognizeDist;

	Spawner->MInfo.Speed = Info.Speed;
	Spawner->MInfo.RunSpeed = Info.RunSpeed;
	Spawner->MInfo.EXP = Info.EXP;
}

