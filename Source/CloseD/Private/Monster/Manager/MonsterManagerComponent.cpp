// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Manager/MonsterManagerComponent.h"

#include "Monster/MonsterBase.h"

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

void UMonsterManagerComponent::SpawnMonster()
{
	for(auto& Elem : MonsterInfo)
	{
		AMonsterBase* SpawnedMonster = GetWorld()->SpawnActor<AMonsterBase>(Elem.Key, GetOwner()->GetActorLocation(), FRotator::ZeroRotator);
		SetMonsterInfo(SpawnedMonster, Elem.Value);
	}
}

void UMonsterManagerComponent::SetMonsterInfo(AMonsterBase* SpawnMonster, FMonsterSpawnInfo& Info)
{
	SpawnMonster->MonsterInfo.Max_Hp = Info.Max_Hp;

	SpawnMonster->MonsterInfo.Attack = Info.Attack;
	SpawnMonster->MonsterInfo.Defense = Info.Defense;

	SpawnMonster->MonsterInfo.Penetration = Info.Penetration;

	SpawnMonster->MonsterInfo.AttackDist = Info.AttackDist;
	SpawnMonster->MonsterInfo.RecognizeDist = Info.RecognizeDist;

	SpawnMonster->MonsterInfo.Speed = Info.Speed;
	SpawnMonster->MonsterInfo.RunSpeed = Info.RunSpeed;
	SpawnMonster->MonsterInfo.EXP = Info.EXP;

}

