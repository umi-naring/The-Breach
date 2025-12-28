// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MonsterBase.generated.h"

UCLASS()
class AMonsterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonsterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float Max_Hp;//최대 체력
	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float Current_HP;//현재 체력

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float Attack;//공격력
	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float Defense;//방어력

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float Penetration;//방어력 관통

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float AttackDist;//공격 사거리

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float Speed;//속도

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float EXP;//죽인 말한테 들어가는 경험치

	bool CanSkill = false;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCursor
	) override;

	float GetDamage();
	float GetPenetration();
	float GetAttackDist();
};
