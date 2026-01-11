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
	GetWorld()->SpawnActor<AMonsterBase>(GetOwner()->GetClass(), GetOwner()->GetActorTransform());
}

void UMonsterManagerComponent::SetMonsterInfo(AMonsterBase* SpawnMonster)
{
	SpawnMonster->MonsterInfo.Max_Hp = MInfo.Max_Hp;

	SpawnMonster->MonsterInfo.Attack = MInfo.Attack;
	SpawnMonster->MonsterInfo.Defense = MInfo.Defense;

	SpawnMonster->MonsterInfo.Penetration = MInfo.Penetration;

	SpawnMonster->MonsterInfo.AttackDist = MInfo.AttackDist;

	SpawnMonster->MonsterInfo.RecognizeDist = MInfo.RecognizeDist;

	SpawnMonster->MonsterInfo.Speed = MInfo.Speed;
	SpawnMonster->MonsterInfo.RunSpeed = MInfo.RunSpeed;

	SpawnMonster->MonsterInfo.EXP = MInfo.EXP;

}

