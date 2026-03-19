// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Unit/MeleeUnitBase.h"
#include "Character/Unit/UnitAIController/AllUnitController.h"
#include "Character/CharacterBase.h"

void AMeleeUnitBase::NotifyMeleeHit()
{
	AAllUnitController* LocalController = Cast<AAllUnitController>(GetController());
	if (!LocalController || !IsAttacking)
		return;

	if (ACharacterBase* TargetCharacter = Cast<ACharacterBase>(LocalController->GetCurrentTarget()))
		TargetCharacter->ApplyDamage(GetAttackPower());
}
