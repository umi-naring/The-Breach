// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AllController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Character.h"
#include "AllUnitController.generated.h"

class AUnitBase;

UCLASS()
class CLOSED_API AAllUnitController : public AAllController
{
	GENERATED_BODY()

private:
	AUnitBase* Owner = nullptr;
	AActor* CurrentTarget = nullptr;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TArray<AActor*> OverlapActors;
	TArray<AActor*> IgnoreActors;

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

	void Attack();

public:
	void UnitMoveToLocation(FVector TargetLocation);
	AActor* GetCurrentTarget() const { return CurrentTarget; }

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

	AActor* FindClosestTarget(float SearchRadius);
	bool IsInAttackRange(AActor* Target) const;
};
