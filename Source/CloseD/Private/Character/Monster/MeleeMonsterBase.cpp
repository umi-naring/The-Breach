// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Monster/MeleeMonsterBase.h"
#include "Character/CharacterBase.h"

void AMeleeMonsterBase::NotifyMeleeHit()
{
	if (!IsAttacking || !GetCurrentTarget())
		return;

	if (ACharacterBase* TargetCharacter = Cast<ACharacterBase>(GetCurrentTarget()))
		TargetCharacter->ApplyDamage(GetAttackPower());
}
