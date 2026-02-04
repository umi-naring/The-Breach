// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AllController.h"

#include "Kismet/GameplayStatics.h"

#include "Character/Monster/MonsterBase.h"
#include "Character/Unit/UnitBase.h"

#include "AllMonsterController.generated.h"

UCLASS()
class AAllMonsterController : public AAllController
{
	GENERATED_BODY()
protected:
	AMonsterBase* Owner;

public:
	bool HasTargetUnit = false;

private:
	virtual void OnPossess(APawn* InPawn) override;

	void InitSetting();

	//µø¿€
	void ExecuteMove(AActor* Target);

private:
	float GetEffectiveRange(const AActor* Target) const
	{
		const ACharacter* OwnerCharacter = Cast<ACharacter>(Owner);
		const ACharacter* TargetCharacter = Cast<ACharacter>(Target);

		const float OwnerRadius = OwnerCharacter ? OwnerCharacter->GetSimpleCollisionRadius() : 0.f;
		const float TargetRadius = TargetCharacter ? TargetCharacter->GetSimpleCollisionRadius() : 0.f;

		const float Base = OwnerRadius + TargetRadius;

		return (Base * 1.5f) + 30.f;
	}

protected:
	AAllMonsterController();
	virtual void Tick(float DeltaTime) override;

public:
	void RequestMoveToTarget(AActor* InTarget);

	bool IsInAttackRange() const
	{
		if (!Owner || !Owner->GetCurrentTarget())
			return false;

		const float AttackRange = Owner->GetStats(EStatsType::ATTACK_DIST);
		const float EffectiveRange = AttackRange + GetEffectiveRange(Owner->GetCurrentTarget());

		return FVector::DistSquared2D(
			Owner->GetActorLocation(),
			Owner->GetCurrentTarget()->GetActorLocation()
		) <= FMath::Square(EffectiveRange);
	}

	bool IsInRecognizeRange(AActor* Target) const
	{
		if (!Owner || !Target) 
			return false;

		const float RecognizeRange = Owner->GetStats(EStatsType::RECOGNIZE_DIST);
		const float EffectiveRange = RecognizeRange + GetEffectiveRange(Target);

		return FVector::DistSquared2D(
			Owner->GetActorLocation(),
			Target->GetActorLocation()
		) <= FMath::Square(EffectiveRange);
	}
};
