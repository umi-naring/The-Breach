// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AIController/AllAIController.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Animation/AnimMontage.h"

#include "MonsterBase.generated.h"

class UHealthComponent;

UENUM(BlueprintType)
enum class EStatsType :uint8
{
	HP,
	ATTACK,
	DEFENSE,
	PENETRATION,
	ATTACK_DIST,
	RECOGNIZE_DIST,
	SPEED,
	RUNSPEED
};

//USTRUCT(BlueprintType)
//struct FMonsterInfo
//{
//	GENERATED_BODY()
//
//	UPROPERTY(EditDefaultsOnly, Category = "Info")
//	float Max_Hp;//최대 체력
//
//	UPROPERTY(EditDefaultsOnly, Category = "Info")
//	float Attack;//공격력
//
//	float Current_HP;//현재 체력
//
//	UPROPERTY(EditDefaultsOnly, Category = "Info")
//	float Defense;//방어력
//
//	UPROPERTY(EditDefaultsOnly, Category = "Info")
//	float Penetration;//방어력 관통
//
//	UPROPERTY(EditDefaultsOnly, Category = "Info")
//	float AttackDist;//공격 사거리
//
//	UPROPERTY(EditDefaultsOnly, Category = "Info")
//	float RecognizeDist;//인식 사거리
//
//	UPROPERTY(EditDefaultsOnly, Category = "Info")
//	float Speed;//속도
//
//	UPROPERTY(EditDefaultsOnly, Category = "Info")
//	float RunSpeed;//달리는 속도
//
//	UPROPERTY(EditDefaultsOnly, Category = "Info")
//	float EXP;//죽인 말한테 들어가는 경험치
//};

UCLASS()
class AMonsterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonsterBase();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Montage")
	UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montage")
	UAnimMontage* DeathMontage; 

	UPROPERTY(VisibleDefaultsOnly, Category = "Stats")
	UHealthComponent* HealthComp;

protected:
	bool CanSkill = false;
	TMap<EStatsType, float> Stats;

public:/*
	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	FMonsterInfo MonsterInfo;*/
	
	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	float NowSpeed;

protected:
	void OnStatEvent(EStatsType Type);

public:
	void InitInfo(EStatsType Type, float _statValue);
	void PlayAttackMontage();
	void SetSpeed();

	float GetStats(EStatsType Type) const
	{
		if (const float* Value = Stats.Find(Type))
			return *Value;

		return 0.f;
	}
};
