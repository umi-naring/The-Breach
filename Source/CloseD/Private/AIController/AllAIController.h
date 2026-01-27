// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "Kismet/GameplayStatics.h"

#include "AllAIController.generated.h"

class AMonsterBase;
class AUnitBase;

UCLASS()
class AAllAIController : public AAIController
{
	GENERATED_BODY()
protected:
	AMonsterBase* Owner;
	AActor* TargetActor;

public:
	bool HasTargetUnit = false;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	bool IsAttacking = false;

private:
	virtual void OnPossess(APawn* InPawn) override;
	void InitNexusTarget();

	//µø¿€
	void MoveToTarget();
	void AttackTarget();

protected:
	AAllAIController();

};
