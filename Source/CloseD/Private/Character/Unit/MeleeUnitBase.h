// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Unit/UnitBase.h"
#include "MeleeUnitBase.generated.h"

UCLASS()
class CLOSED_API AMeleeUnitBase : public AUnitBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void NotifyMeleeHit();
};
