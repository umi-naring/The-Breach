// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

#include "AllUnitController.generated.h"

/**
 * 
 */
UCLASS()
class AAllUnitController : public AAIController
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, Category = "AI")
	UBehaviorTree* Behavior;
private:
	AAllUnitController();
	virtual void OnPossess(APawn* InPawn) override;
public:
	void UnitMoveToLocation(FVector TargetLocation);
};
