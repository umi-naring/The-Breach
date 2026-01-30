// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "System/GameInstanceSubsystem/MonsterDataSubsystem.h"

#include "Character/CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Animation/AnimMontage.h"

#include "MonsterBase.generated.h"

class AAllAIController;

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
	TMap<EStatsType, float> Stats;

public:
	FMonsterInfo MonsterInfo;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	bool IsRun = false;
	UPROPERTY(BlueprintReadWrite, Category = "State")
	bool IsAttacking = false;

	bool CanSkill = false;

	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	float NowSpeed;

public:
	void InitInfo(EStatsType Type, float _statValue);
	void OnStatEvent(EStatsType Type);

	void PlayAttack();
	void SetSpeed();

	float GetStats(EStatsType Type) const
	{
		if (const float* Value = Stats.Find(Type))
			return *Value;

		return 0.f;
	}
};
