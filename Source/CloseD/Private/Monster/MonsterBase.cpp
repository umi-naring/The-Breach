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