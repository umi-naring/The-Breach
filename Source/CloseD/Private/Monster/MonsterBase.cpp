// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterBase.h"

#include "System/Component/HealthComponent.h"

AMonsterBase::AMonsterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

void AMonsterBase::InitInfo(EStatsType Type, float _statValue)
{
	Stats.Add(Type, _statValue);
 
	OnStatChanged(Type);
}

void AMonsterBase::OnStatChanged(EStatsType Type)
{
	if (EStatsType::HP == Type)
		HealthComp->SetHP(GetStats(EStatsType::HP));
	
	else if (EStatsType::SPEED == Type)
		GetCharacterMovement()->MaxWalkSpeed = GetStats(EStatsType::SPEED);
}

void AMonsterBase::PlayAttackMontage()
{
	if (!AttackMontage)
		return;
	
	PlayAnimMontage(AttackMontage);
}
//대미지 로직 사라짐
void AMonsterBase::SetSpeed()
{
	AAllAIController* OwnerAIController = Cast<AAllAIController>(GetController());
	if (!OwnerAIController)
		return;

	UBlackboardComponent* BBComp = OwnerAIController->GetBlackboardComponent();
	if (!BBComp)
		return;

	if (OwnerAIController->IsAttacking)
		GetCharacterMovement()->MaxWalkSpeed = 0.f;
	//else if (BBComp->GetValueAsInt("TargetUnit") == 1)
	//	GetCharacterMovement()->MaxWalkSpeed = NowSpeed = MonsterInfo.RunSpeed;
	//else
	//	GetCharacterMovement()->MaxWalkSpeed = NowSpeed = MonsterInfo.Speed;
}