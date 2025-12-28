// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "AllUnitController.generated.h"

/**
 * 
 */
UCLASS()
class AAllUnitController : public AAIController
{
	GENERATED_BODY()
private:
	AAllUnitController();

	virtual void OnPossess(APawn* InPawn) override;

public:
	void UnitMoveToLocation(FVector TargetLocation);
};
