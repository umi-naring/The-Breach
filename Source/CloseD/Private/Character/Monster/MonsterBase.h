// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "System/GameInstanceSubsystem/MonsterDataSubsystem.h"

#include "Animation/AnimMontage.h"

#include "MonsterBase.generated.h"

// System
class ABlockGameMode;

// Monster
class AAllMonsterController;

// Unit
class AUnitBase;

// 몬스터 스탯 종류
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
	RUNSPEED,
	Value
};

UCLASS()
class AMonsterBase : public ACharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonsterBase();

protected:
	ABlockGameMode* GM;

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
	void InitAttackSphere();
	void OnUnitBeginOverlap(AActor* OtherActor);
	void OnUnitEndOverlap(AActor* OtherActor);
	void OnTargetUnitDead();

	bool CanChangeTarget(AActor* NewTarget) const;
	void SetTarget_Internal(AActor* NewTarget);

	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	AUnitBase* GetClosestOverlappingUnit() const;

public:
	void InitInfo(EStatsType Type, float _statValue);
	void OnStatEvent(EStatsType Type);

	void PlayAttack();
	void StopAttack();
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

public:
	bool IsAttackMontagePlaying() const;

	float GetAttackPower() const
	{
		return GetStats(EStatsType::ATTACK);
	}
};
