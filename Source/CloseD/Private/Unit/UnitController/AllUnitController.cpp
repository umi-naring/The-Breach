// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit/UnitController/AllUnitController.h"

#include "Unit/UnitBase.h"

AAllUnitController::AAllUnitController()
{
	
}

void AAllUnitController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AAllUnitController::UnitMoveToLocation(FVector TargetLocation)
{
	AUnitBase* Unit = Cast<AUnitBase>(GetPawn());
	if (!Unit)
		return;

	MoveToLocation(TargetLocation);
}