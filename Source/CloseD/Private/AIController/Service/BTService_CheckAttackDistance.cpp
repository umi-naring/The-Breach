// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController/Service/BTService_CheckAttackDistance.h"

#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "AIController/AllAIController.h"
#include "Monster/MonsterBase.h"

UBTService_CheckAttackDistance::UBTService_CheckAttackDistance()
{
	bNotifyBecomeRelevant = true;
	bNotifyTick = true;
}

void UBTService_CheckAttackDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAllAIController* OwnerAIController = Cast<AAllAIController>(OwnerComp.GetAIOwner());
	if (!OwnerAIController)
		return;

	AMonsterBase* Owner = Cast<AMonsterBase>(OwnerAIController->GetPawn());
	if (!Owner)
		return;

	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	if (!BBComp)
		return;
	
	AActor* TargetActor = Cast<AActor>(BBComp->GetValueAsObject("TargetActor"));
	if (!TargetActor)
		return;

	float Dist = FVector::Dist(TargetActor->GetActorLocation(), Owner->GetActorLocation());

	if (Dist <= Owner->GetAttackDist())
		BBComp->SetValueAsInt("CanAttack", 1);
	else
		BBComp->SetValueAsInt("CanAttack", 0);
}