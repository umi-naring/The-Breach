// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Unit/UnitBase.h"
#include "AIController/AllAIController.h"

#include "Nexus.h"

#include "BTService_SelectAction.generated.h"

/**
 * 
 */
UCLASS()
class UBTService_SelectAction : public UBTService_BlackboardBase
{
	GENERATED_BODY()
private:
	AAllAIController* OwnerAIController;

	UBlackboardComponent* BBComp;

	ANexus* TargetNexus;

	AUnitBase* NearTarget;

	float NearDist;

	TMap<AUnitBase*, float> UnitDistance;

private:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	void UnitDistanceArray();
	void SelectTarget(UBehaviorTreeComponent& OwnerComp);

public:
	UBTService_SelectAction();
};
