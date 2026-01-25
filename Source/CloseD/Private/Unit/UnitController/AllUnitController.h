// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AllUnitController.generated.h"

class AUnitBase;

UCLASS()
class AAllUnitController : public AAIController
{
	GENERATED_BODY()

private:
	AUnitBase* OwnerUnit = nullptr;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TArray<AActor*> OverlapActors;
	TArray<AActor*> IgnoreActors;

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

	void Attack();
	void DistanceToMonster();

public:
	void UnitMoveToLocation(FVector TargetLocation);
};
