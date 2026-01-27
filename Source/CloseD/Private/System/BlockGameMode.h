// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BlockGameMode.generated.h"

class ANexus;

UCLASS()
class ABlockGameMode : public AGameModeBase
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly, Category = "Nexus")
	TSubclassOf<ANexus> NexusClass;

	UPROPERTY(EditDefaultsOnly, Category = "Cost")
	int _firstCost = 5;

	UPROPERTY(EditDefaultsOnly, Category = "Cost")
	int _addCost = 10;

	int _remainCost;

public:
	int _currentWave;

private:
	ABlockGameMode();

public:
	float GetCalculate(float A_Attack, float A_Penetration, float B_Defense);

	bool TryConsumeWaveCost(int Cost);

	AActor* GetNexus();

};
