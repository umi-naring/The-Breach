// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit/UnitController/AllUnitController.h"

#include "Unit/UnitBase.h"
#include "Monster/MonsterBase.h"

void AAllUnitController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OwnerUnit = Cast<AUnitBase>(GetOwner());
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

}

void AAllUnitController::DistanceToMonster()
{
	UKismetSystemLibrary::SphereOverlapActors(
		GetWorld(),
		OwnerUnit->GetActorLocation(),
		OwnerUnit->UnitInfo->AttackDist,
		ObjectTypes,
		AMonsterBase::StaticClass(),
		IgnoreActors,
		OverlapActors
	);
}