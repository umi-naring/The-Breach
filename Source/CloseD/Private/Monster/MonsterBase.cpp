// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterBase.h"

// Sets default values
AMonsterBase::AMonsterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMonsterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonsterBase::Tick(float DeltaTime)
{ 
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMonsterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AMonsterBase::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCursor)
{
	const float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCursor);

	if (Damage < 0)
		return 0;

	Current_HP -= Damage;

	if (Current_HP <= 0)
	{
		this->Destroy();
		return Damage;
	}

	return Damage;
}

float AMonsterBase::GetDamage() { return Attack; }
float AMonsterBase::GetPenetration() { return Penetration; }
float AMonsterBase::GetAttackDist() { return AttackDist; }