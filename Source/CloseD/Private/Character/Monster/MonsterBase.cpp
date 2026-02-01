// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Monster/MonsterBase.h"

#include "Character/Monster/MonsterAIController/AllMonsterController.h"

#include "System/Component/HealthComponent.h"
#include "System/Component/AttackComponent.h"

#include "Character/Unit/UnitBase.h"

AMonsterBase::AMonsterBase()
{
	PrimaryActorTick.bCanEverTick = false;
}
void AMonsterBase::BeginPlay()
{
	Super::BeginPlay();

	InitMovementState();
}

void AMonsterBase::InitMovementState()
{
	GetWorldTimerManager().SetTimer(
		MovementStateTimer,
		this,
		&AMonsterBase::UpdateMovementState,
		0.2f,   // 0.2~0.3√ ∏È √Ê∫–
		true
	);
}

void AMonsterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	Controller = Cast<AAllMonsterController>(GetController());

	SetTarget_Internal(NexusTarget);

	if (Controller)
		Controller->RequestMoveToTarget(CurrentTarget);
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
			SetSpeed();
			break;

		default:
			break;
	}
}

void AMonsterBase::PlayAttack()
{
	IsAttacking = true;
	SetSpeed();

	if (Controller)
		Controller->StopMovement();

	AttackComp->Attack(EAttackType::Normal);
}

void AMonsterBase::OnAttackFinished()
{
	IsAttacking = false;

	if (!Controller || !CurrentTarget)
		return;

	if (!IsAttacking && Controller->IsInAttackRange())
		PlayAttack();
	else
	{
		SetSpeed();
		Controller->RequestMoveToTarget(CurrentTarget);
	}
}

void AMonsterBase::SetSpeed()
{
	float NewSpeed = 0.f;

	if (IsAttacking)
		NewSpeed = 0.f;
	else if (IsRun)
		NewSpeed = MonsterInfo.RunSpeed;
	else
		NewSpeed = MonsterInfo.Speed;

	GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
}

void AMonsterBase::OnUnitBeginOverlap(AActor* OtherActor)
{
	if (CurrentTarget != NexusTarget)
		return; // ¿ÃπÃ ¿Ø¥÷ ≈∏∞Ÿ ¿÷¿Ω

	AUnitBase* Unit = Cast<AUnitBase>(OtherActor);
	if (!Unit) return;

	SetTarget_Internal(Unit);
}

void AMonsterBase::OnUnitEndOverlap(AActor* OtherActor)
{
	if (OtherActor != CurrentTarget)
		return;

	// ≈∏∞Ÿ ¿Ø¥÷¿Ã ¿Ã≈ª
	SetTarget_Internal(NexusTarget);
}

void AMonsterBase::OnTargetUnitDead()
{
	SetTarget_Internal(NexusTarget);
}

bool AMonsterBase::CanChangeTarget(AActor* NewTarget) const
{
	// √ ±‚ ªÛ≈¬
	if (CurrentTarget == nullptr)
		return true;

	// ¿ÃπÃ ∞∞¿∫ ≈∏∞Ÿ
	if (CurrentTarget == NewTarget)
		return false;

	// ¿Ø¥÷ ≈∏∞Ÿ ¡ﬂ¿œ ∂ß
	if (CurrentTarget != NexusTarget)
		return NewTarget == NexusTarget;

	return true;
}

void AMonsterBase::RequestSetTarget(AActor* NewTarget)
{
	if (!NewTarget) return;

	if (!CanChangeTarget(NewTarget)) return;

	SetTarget_Internal(NewTarget);
}

void AMonsterBase::SetTarget_Internal(AActor* NewTarget)
{
	if (CurrentTarget == NewTarget)
		return;

	CurrentTarget = NewTarget;

	UpdateMovementState();

	if (Controller)
		Controller->RequestMoveToTarget(CurrentTarget);
}

void AMonsterBase::UpdateMovementState()
{
	if (!Controller || !CurrentTarget) return;

	bool bShouldRun = Controller->IsInRecognizeRange(CurrentTarget);

	if (IsRun != bShouldRun)
	{
		IsRun = bShouldRun;
		SetSpeed();
	}
}

void AMonsterBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorldTimerManager().ClearTimer(MovementStateTimer);
	Super::EndPlay(EndPlayReason);
}