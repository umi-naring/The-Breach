// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BlockGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ABlockGameMode : public AGameModeBase
{
	GENERATED_BODY()
private:
	ABlockGameMode();
public:
	float GetCalculate(float A_Attack, float A_Penetration, float B_Defense);
};
