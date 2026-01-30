// Fill out your copyright notice in the Description page of Project Settings.


#include "System/Component/AttackComponent.h"
#include "Character/CharacterBase.h"

// Sets default values for this component's properties
UAttackComponent::UAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Owner = Cast<ACharacterBase>(GetOwner());

}


// Called every frame
void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAttackComponent::Attack(EAttackType Type)
{
	switch (Type)
	{
	case EAttackType::Normal:
		NormalAttack();
		break;
	case EAttackType::Skill:
		SkillAttack();
		break;
	case EAttackType::Ultimate:
		UltimateAttack();
		break;
	}
}

void UAttackComponent::NormalAttack()
{
	if (!Owner->Attack_Montage)
		return;

	Owner->PlayAnimMontage(Owner->Attack_Montage);
}

void UAttackComponent::SkillAttack()
{
	/*if (!Owner->Skill_Attack_Montage)
		return;

	Owner->PlayAnimMontage(Owner->Skill_Attack_Montage);*/
}

void UAttackComponent::UltimateAttack()
{
	/*if (!Owner->Ultimate_Attack_Montage)
		return;

	Owner->PlayAnimMontage(Owner->Ultimate_Attack_Montage);*/
}