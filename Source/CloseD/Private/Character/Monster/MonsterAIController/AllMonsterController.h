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

	//µ¿ÀÛ
	void ExecuteMove(AActor* Target);

protected:
	AAllMonsterController();

public:
	void RequestMoveToTarget(AActor* InTarget);

	bool IsInAttackRange() const
	{
		if (!Owner || !Owner->GetCurrentTarget())
			return false;

		const float AttackRange = Owner->GetStats(EStatsType::ATTACK_DIST);

		return FVector::DistSquared(
			Owner->GetActorLocation(),
			Owner->GetCurrentTarget()->GetActorLocation()
		) <= FMath::Square(AttackRange);
	}

	bool IsInRecognizeRange(AActor* Target) const
	{
		if (!Owner || !Target) 
			return false;

		return FVector::DistSquared(
			Owner->GetActorLocation(),
			Target->GetActorLocation()
		) <= FMath::Square(Owner->GetStats(EStatsType::RECOGNIZE_DIST));
	}
};
