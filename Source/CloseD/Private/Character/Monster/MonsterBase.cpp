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
		0.2f,   // 0.2~0.3초면 충분
		true
	);
}

void AMonsterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	Controller = Cast<AAllMonsterController>(GetController());

	SetTarget_Internal(NexusTarget);

	FTimerHandle DelayMove;

	//임시(나중에는 스포너에서 호출 예정), 디버그 모드로 놓을 예정
	GetWorld()->GetTimerManager().SetTimer(DelayMove, [this]() {
		if (Controller)
			Controller->RequestMoveToTarget(CurrentTarget);
		}, 0.5f, false);
	
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
		return; // 이미 유닛 타겟 있음

	AUnitBase* Unit = Cast<AUnitBase>(OtherActor);
	if (!Unit) return;

	SetTarget_Internal(Unit);
}

void AMonsterBase::OnUnitEndOverlap(AActor* OtherActor)
{
	if (OtherActor != CurrentTarget)
		return;

	// 타겟 유닛이 이탈
	SetTarget_Internal(NexusTarget);
}

void AMonsterBase::OnTargetUnitDead()
{
	SetTarget_Internal(NexusTarget);
}

bool AMonsterBase::CanChangeTarget(AActor* NewTarget) const
{
	// 초기 상태
	if (CurrentTarget == nullptr)
		return true;

	// 이미 같은 타겟
	if (CurrentTarget == NewTarget)
		return false;

	// 유닛 타겟 중일 때
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
	if (!Controller || !CurrentTarget)
		return;

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