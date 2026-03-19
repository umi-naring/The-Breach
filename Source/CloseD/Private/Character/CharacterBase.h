// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "System/GameInstanceSubsystem/MonsterDataSubsystem.h"

#include "Components/SphereComponent.h"
#include "System/Component/HealthComponent.h"
#include "System/Component/AttackComponent.h"

#include "CharacterBase.generated.h"

UCLASS()
class ACharacterBase : public ACharacter
{
	GENERATED_BODY()
protected:	
	UPROPERTY(VisibleAnywhere, Category = "AttackSphere")
	USphereComponent* AttackSphere;

	// ¾×ÅÍ ÄÄÆ÷³ÍÆ®
	UPROPERTY(VisibleDefaultsOnly, Category = "Stats")
	UHealthComponent* HealthComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Stats")
	UAttackComponent* AttackComp;

	TSet<AActor*> TargetInAttackRange;

	bool bIsDead = false;

public:
	// ¸ùÅ¸ÁÖ
	UPROPERTY(EditDefaultsOnly, Category = "Montage")
	UAnimMontage* Attack_Montage;

	UPROPERTY(EditDefaultsOnly, Category = "Montage")
	UAnimMontage* Death_Montage;

private:
	void SettingBind();
	void InitAttackSphere();

	UFUNCTION()
	void OnTargetBegin(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnTargetEnd(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

public:
	// Sets default values for this character's properties
	ACharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnDead();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void ApplyDamage(float Damage);

	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;
};
