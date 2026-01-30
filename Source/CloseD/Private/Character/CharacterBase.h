// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "System/Component/HealthComponent.h"
#include "System/Component/AttackComponent.h"

#include "CharacterBase.generated.h"

UCLASS()
class ACharacterBase : public ACharacter
{
	GENERATED_BODY()
protected:
	// ¾×ÅÍ ÄÄÆ÷³ÍÆ®
	UPROPERTY(VisibleDefaultsOnly, Category = "Stats")
	UHealthComponent* HealthComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Stats")
	UAttackComponent* AttackComp;

public:
	// ¸ùÅ¸ÁÖ
	UPROPERTY(EditDefaultsOnly, Category = "Montage")
	UAnimMontage* Attack_Montage;

	UPROPERTY(EditDefaultsOnly, Category = "Montage")
	UAnimMontage* Death_Montage;

public:
	// Sets default values for this character's properties
	ACharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
