// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AIController/AllAIController.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackBoardComponent.h"

#include "Animation/AnimMontage.h"

#include "MonsterBase.generated.h"

USTRUCT(BlueprintType)
struct FMonsterInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	float Max_Hp;//최대 체력

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	float Attack;//공격력

	float Current_HP;//현재 체력

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	float Defense;//방어력

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	float Penetration;//방어력 관통

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	float AttackDist;//공격 사거리

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	float RecognizeDist;//인식 사거리

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	float Speed;//속도

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	float RunSpeed;//달리는 속도

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	float EXP;//죽인 말한테 들어가는 경험치
};

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

protected:
	bool CanSkill = false;

public:
	FMonsterInfo MonsterInfo;

	UPROPERTY(BlueprintReadOnly, Category = "Stats")
		float NowSpeed;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:	
	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCursor
	) override;

	void PlayAttackMontage();
	void SetSpeed();

	float GetDamage() { return MonsterInfo.Attack; }
	float GetSpeed() { return NowSpeed; }
	float GetPenetration() { return MonsterInfo.Penetration; }
	float GetAttackDist() { return MonsterInfo.AttackDist; }
	float GetRecognizeDist() { return MonsterInfo.RecognizeDist; }

};
