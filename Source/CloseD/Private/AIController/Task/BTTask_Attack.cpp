// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"

#include "AIController/AllAIController.h"
#include "Monster/MonsterBase.h"

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAllAIController* AIOwner = Cast<AAllAIController>(OwnerComp.GetAIOwner());
	if (!AIOwner)
		return EBTNodeResult::Failed;

	AMonsterBase* Monster = Cast<AMonsterBase>(AIOwner->GetPawn());
	if (!Monster)
		return EBTNodeResult::Failed;

	Monster->PlayAttackMontage();

	return EBTNodeResult::Succeeded;
}