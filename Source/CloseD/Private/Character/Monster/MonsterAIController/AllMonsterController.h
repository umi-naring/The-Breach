// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AllController.h"

#include "Kismet/GameplayStatics.h"

#include "AllMonsterController.generated.h"

class AMonsterBase;
class AUnitBase;

UCLASS()
class AAllMonsterController : public AAllController
{
	GENERATED_BODY()
protected:
	AMonsterBase* Owner;

public:
	bool HasTargetUnit = false;

private:
	virtual void OnPossess(APawn* InPawn) override;
	void InitNexusTarget();

	//µø¿€
	void Move();
	void MoveToTarget();

	void AttackTarget();

protected:
	AAllMonsterController();

};
