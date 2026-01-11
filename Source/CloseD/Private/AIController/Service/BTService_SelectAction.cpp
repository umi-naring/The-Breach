// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController/Service/BTService_SelectAction.h"

#include "Unit/UnitBase.h"
#include "Monster/MonsterBase.h"

#include "AIController/AllAIController.h"

#include "Nexus.h"

UBTService_SelectAction::UBTService_SelectAction()
{
	bNotifyBecomeRelevant = true;
	bNotifyTick = true;
}

void UBTService_SelectAction::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	SelectTarget(OwnerComp);
}

void UBTService_SelectAction::SelectTarget(UBehaviorTreeComponent& OwnerComp)
{
	if (!IsValid(TargetNexus))
	{
		TArray<AActor*> EveryNexus;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANexus::StaticClass(), EveryNexus);

		if (EveryNexus.Num() <= 0)
			return;
		TargetNexus = Cast<ANexus>(EveryNexus[0]);
	}

	OwnerAIController = Cast<AAllAIController>(OwnerComp.GetAIOwner());
	if (!OwnerAIController)
		return;

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

		if (NearDist <= OwnerMonster->GetRecognizeDist())
		{
			BBComp->SetValueAsInt("TargetUnit", 1);
			BBComp->SetValueAsObject("TargetActor", NearTarget);
		}
		else
		{
			BBComp->SetValueAsInt("TargetUnit", 0);
			BBComp->SetValueAsInt("TargetNexus", 1);
			BBComp->SetValueAsObject("TargetActor", TargetNexus);
			OwnerAIController->HasTargetUnit = false;
		}
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

