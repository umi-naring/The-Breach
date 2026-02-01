// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "System/GameInstanceSubsystem/MonsterDataSubsystem.h"

#include "Character/CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Animation/AnimMontage.h"

#include "MonsterBase.generated.h"

class AAllMonsterController;
class AUnitBase;

UENUM(BlueprintType)
enum class EStatsType :uint8
{
	HP = 0,
	ATTACK,
	DEFENSE,
	PENETRATION,
	ATTACK_DIST,
	RECOGNIZE_DIST,
	SPEED,
	RUNSPEED
};

UCLASS()
class AMonsterBase : public ACharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonsterBase();

protected:
	FTimerHandle MovementStateTimer;

	AAllMonsterController* Controller = nullptr;

	TMap<EStatsType, float> Stats;

	AActor* CurrentTarget;
	AActor* NexusTarget;

	TSet<AUnitBase*> OverlappingUnits;

public:
	FMonsterInfo MonsterInfo;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	bool IsRun = false;
	UPROPERTY(BlueprintReadWrite, Category = "State")
	bool IsAttacking = false;

	bool CanSkill = false;

	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	float NowSpeed;

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//Move
	void InitMovementState();
	void UpdateMovementState();

	//Recognize
	void OnUnitBeginOverlap(AActor* OtherActor);
	void OnUnitEndOverlap(AActor* OtherActor);
	void OnTargetUnitDead();

	bool CanChangeTarget(AActor* NewTarget) const;
	void SetTarget_Internal(AActor* NewTarget);


public:
	void InitInfo(EStatsType Type, float _statValue);
	void OnStatEvent(EStatsType Type);

	void PlayAttack();
	UFUNCTION(BlueprintCallable)
	void OnAttackFinished();

	void SetSpeed();
	void RequestSetTarget(AActor* NewTarget);

	float GetStats(EStatsType Type) const
	{
		if (const float* Value = Stats.Find(Type))
			return *Value;

		return 0.f;
	}

	AActor* GetCurrentTarget() { return CurrentTarget; }
};
