// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController/Task/BTTask_MoveToTarget.h"

#include "AIController/AllAIController.h"
#include "Monster/MonsterBase.h"

EBTNodeResult::Type UBTTask_MoveToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAllAIController* OwnerAIController = Cast<AAllAIController>(OwnerComp.GetAIOwner());
	if (!OwnerAIController)
		return EBTNodeResult::Failed;;

	AMonsterBase* Owner = Cast<AMonsterBase>(OwnerAIController->GetPawn());
	if (!Owner)
		return EBTNodeResult::Failed;;
	
	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	if (!BBComp)
		return EBTNodeResult::Failed;;

	AActor* Target = Cast<AActor>(BBComp->GetValueAsObject("TargetActor"));
	if (!Target)
		return EBTNodeResult::Failed;

	FVector TargetLocation = Target->GetActorLocation();
	OwnerAIController->MoveToLocation(
		TargetLocation,
		Owner->GetAttackDist(),
		true,
		true,
		true, 
		false, 
		nullptr, 
		true
	);
	return EBTNodeResult::Succeeded;
}