// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit/UnitController/AllUnitController.h"

#include "Unit/UnitBase.h"

AAllUnitController::AAllUnitController()
{
	
}

void AAllUnitController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (Behavior)
	{
		RunBehaviorTree(Behavior);
	}
}

void AAllUnitController::UnitMoveToLocation(FVector TargetLocation)
{
	UBlackboardComponent* UnitBlackboard = Cast<UBlackboardComponent>(GetBlackboardComponent());
	if (!UnitBlackboard)
		return;

	AUnitBase* Unit = Cast<AUnitBase>(GetPawn());
	if (!Unit)
		return;

	MoveToLocation(TargetLocation);
}