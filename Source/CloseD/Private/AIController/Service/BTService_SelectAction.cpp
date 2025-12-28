// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController/Service/BTService_SelectAction.h"

UBTService_SelectAction::UBTService_SelectAction()
{
	bNotifyBecomeRelevant = true;
	bNotifyTick = true;
}

void UBTService_SelectAction::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (!IsValid(TargetNexus))
	{
		TArray<AActor*> EveryNexus;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANexus::StaticClass(), EveryNexus);

		TargetNexus = Cast<ANexus>(EveryNexus[0]);
	}
	AMonsterBase* OwnerMonster = Cast<AMonsterBase>(OwnerAIController->GetPawn());
	if (!OwnerMonster)
		return;

	OwnerAIController = Cast<AAllAIController>(OwnerComp.GetAIOwner());
	if (!OwnerAIController)
		return;

	BBComp = OwnerComp.GetBlackboardComponent();
	if (!BBComp)
		return;
	
	if (!OwnerAIController->HasTargetUnit)
	{
		UnitDistanceArray();
		UnitDistance.ValueSort([](const float& A, const float& B) { return A < B; });
		for (auto& Elem : UnitDistance)
		{
			NearTarget = Elem.Key;
			NearDist = Elem.Value;
			break; // 정렬 후 첫 번째
		}

		if (NearDist <= OwnerMonster->GetAttackDist())
			BBComp->SetValueAsObject("TargetActor", TargetUnit);
		else
			BBComp->SetValueAsObject("TargetActor", TargetNexus);
	}
}

void UBTService_SelectAction::UnitDistanceArray()
{
	AMonsterBase* OwnerMonster = Cast<AMonsterBase>(OwnerAIController->GetPawn());
	if (!OwnerMonster)
		return;

	TArray<AActor*> EveryUnit;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUnitBase::StaticClass(), EveryUnit);
	if (EveryUnit.Num() <= 0)
		return;

	UnitDistance.Empty();

	for (AActor* Actor : EveryUnit)
	{
		AUnitBase* Unit = Cast<AUnitBase>(Actor);

		if (!Unit)
			continue;

		float Distance = FVector::Dist(
			Unit->GetActorLocation(),
			OwnerMonster->GetActorLocation()
		);

		UnitDistance.Add(Unit, Distance);
	}
}