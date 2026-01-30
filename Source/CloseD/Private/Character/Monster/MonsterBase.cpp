// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Monster/MonsterBase.h"

#include "Character/Monster/MonsterAIController/AllMonsterController.h"

#include "System/Component/HealthComponent.h"
#include "System/Component/AttackComponent.h"

AMonsterBase::AMonsterBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMonsterBase::InitInfo(EStatsType Type, float _statValue)
{
	Stats.Add(Type, _statValue);
 
	OnStatEvent(Type);
}

void AMonsterBase::OnStatEvent(EStatsType Type)
{
	switch (Type)
	{
		case EStatsType::HP:
			HealthComp->SetHP(GetStats(EStatsType::HP));
			break;

		case EStatsType::SPEED:
			GetCharacterMovement()->MaxWalkSpeed = GetStats(EStatsType::SPEED);
			break;

		default:
			break;
	}
}

void AMonsterBase::PlayAttack()
{
	AttackComp->Attack(EAttackType::Normal);
}

//대미지 로직 사라짐
void AMonsterBase::SetSpeed()
{
	if (IsAttacking)
		GetCharacterMovement()->MaxWalkSpeed = 0.f;
	else if (!IsRun)
		GetCharacterMovement()->MaxWalkSpeed = MonsterInfo.Speed;
	else if (IsRun)
		GetCharacterMovement()->MaxWalkSpeed = MonsterInfo.RunSpeed;
	else
		return;
}