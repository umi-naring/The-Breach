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

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

	void Attack();

public:
	void UnitMoveToLocation(FVector TargetLocation);
};
