// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Unit/UnitAIController/AllUnitController.h"

#include "Character/Unit/UnitBase.h"
#include "Character/Monster/MonsterBase.h"

void AAllUnitController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Owner = Cast<AUnitBase>(GetPawn());

	ObjectTypes.Reset();
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	IgnoreActors.Reset();
	if (Owner)
		IgnoreActors.Add(Owner);
}

void AAllUnitController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!Owner)
		return;

	// AttackRange 초기화
	const float AttackRange = Owner->GetAttackRange();

	// AttackRange가 0 이하이면 공격 불가
	if (AttackRange <= 0.f)
		return;

	if (!CurrentTarget || !IsInAttackRange(CurrentTarget))
		CurrentTarget = FindClosestTarget(AttackRange + GetEffectiveRange(CurrentTarget));

	if (!CurrentTarget)
	{
		if (Owner->IsAttacking)
			Owner->StopAttack();
		ClearFocus(EAIFocusPriority::Gameplay);
		return;
	}

	SetFocus(CurrentTarget);

	if (Owner->IsAttacking)
	{
		if (!IsInAttackRange(CurrentTarget))
			Owner->StopAttack();
		return;
	}

	if (Owner->IsAttackMontagePlaying())
		return;

	if (IsInAttackRange(CurrentTarget))
		Owner->PlayAttack();

}

AActor* AAllUnitController::FindClosestTarget(float SearchRadius)
{
	OverlapActors.Reset();

	if (!Owner)
		return nullptr;

	const FVector Origin = Owner->GetActorLocation();

	UKismetSystemLibrary::SphereOverlapActors(
		this,
		Origin,
		SearchRadius,
		ObjectTypes,
		AMonsterBase::StaticClass(),
		IgnoreActors,
		OverlapActors
	);

	AActor* Closest = nullptr;
	float BestDistSq = TNumericLimits<float>::Max();

	for (AActor* Actor : OverlapActors)
	{
		const float DistSq = FVector::DistSquared(Origin, Actor->GetActorLocation());
		if (DistSq < BestDistSq)
		{
			BestDistSq = DistSq;
			Closest = Actor;
		}
	}

	return Closest;
}

bool AAllUnitController::IsInAttackRange(AActor* Target) const
{
	if (!Owner || !Target)
		return false;

	const float Range = Owner->GetAttackRange() + GetEffectiveRange(Target);

	return FVector::DistSquared2D(
		Owner->GetActorLocation(),
		Target->GetActorLocation()
	) <= FMath::Square(Range);
}

void AAllUnitController::UnitMoveToLocation(FVector TargetLocation)
{
	if (!Owner)
		return;

	MoveToLocation(TargetLocation);
}

void AAllUnitController::Attack()
{
	if (Owner)
		Owner->PlayAttack();
}