// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Monster/MonsterBase.h"
#include "MeleeMonsterBase.generated.h"

UCLASS()
class CLOSED_API AMeleeMonsterBase : public AMonsterBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void NotifyMeleeHit();
};
