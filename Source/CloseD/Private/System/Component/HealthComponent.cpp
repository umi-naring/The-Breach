// Fill out your copyright notice in the Description page of Project Settings.


#include "System/Component/HealthComponent.h"
#include "Character/CharacterBase.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	
}
// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::SetHP(float MaxHealth)
{
	Current_HP = Max_HP = MaxHealth;
}

void UHealthComponent::OnTakeDamage(float Damage)
{
	Current_HP = FMath::Clamp(Current_HP - Damage, 0, Max_HP);

	OnDamaged.Broadcast(Damage);

	if (Current_HP <= 0)
		OnDead.Broadcast();
}