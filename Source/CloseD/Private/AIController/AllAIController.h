// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "Kismet/GameplayStatics.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

#include "AllAIController.generated.h"

class AMonsterBase;
class AUnitBase;

UCLASS()
class AAllAIController : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "AI")
	UBehaviorTree* Behavior;

	UBlackboardComponent* BBComp;

	AMonsterBase* Owner;

public:
	bool HasTargetUnit = false;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	bool IsAttacking = false;

private:
	virtual void OnPossess(APawn* InPawn) override;

	void AttackTarget(AUnitBase* HitActor);

protected:
	AAllAIController();
};
