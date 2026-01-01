// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_CheckAttackDistance.generated.h"

/**
 * 
 */
UCLASS()
class UBTService_CheckAttackDistance : public UBTService_BlackboardBase
{
	GENERATED_BODY()
protected:
	UBTService_CheckAttackDistance();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
