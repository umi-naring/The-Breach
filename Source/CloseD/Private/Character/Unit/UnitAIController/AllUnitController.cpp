// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Unit/UnitAIController/AllUnitController.h"

#include "Character/Unit/UnitBase.h"
#include "Character/Monster/MonsterBase.h"

void AAllUnitController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Owner = Cast<AUnitBase>(GetOwner());
}

void AAllUnitController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAllUnitController::UnitMoveToLocation(FVector TargetLocation)
{
	AUnitBase* Unit = Cast<AUnitBase>(GetPawn());
	if (!Unit)
		return;

	MoveToLocation(TargetLocation);
}

void AAllUnitController::Attack()
{
	Owner->PlayAttack();
}
