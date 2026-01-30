// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttack, float, AttackDistance);

class ACharacterBase;

UENUM()
enum class EAttackType : uint8
{
	Normal,
	Skill,
	Charge,
	Ultimate
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UAttackComponent : public UActorComponent
{
	GENERATED_BODY()
private:
	// 공격 패턴 행동 매소드
	void NormalAttack();
	void SkillAttack();
	void UltimateAttack();

	ACharacterBase* Owner;

public:	
	// Sets default values for this component's properties
	UAttackComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public :
	UPROPERTY(BlueprintAssignable)
	FOnAttack OnAttack;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Attack(EAttackType Type);
};
