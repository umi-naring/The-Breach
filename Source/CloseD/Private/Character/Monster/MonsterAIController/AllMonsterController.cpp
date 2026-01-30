// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Monster/MonsterAIController/AllMonsterController.h"

#include "System/BlockGameMode.h"

#include "Character/Monster/MonsterBase.h"
#include "Character/Unit/UnitBase.h"


AAllMonsterController::AAllMonsterController()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AAllMonsterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Owner = Cast<AMonsterBase>(GetPawn());

	InitNexusTarget();
}

void AAllMonsterController::Move()
{
	float Distance = FVector::Dist(Owner->GetActorLocation(), TargetActor->GetActorLocation());

	if (Distance <= Owner->GetStats(EStatsType::RECOGNIZE_DIST))
	{
		Owner->OnStatEvent(EStatsType::SPEED);
	}
}

void AAllMonsterController::InitNexusTarget()
{
	TargetActor = Cast<ABlockGameMode>(GetWorld()->GetAuthGameMode())->GetNexus();
}

void AAllMonsterController::MoveToTarget()
{
	MoveToLocation(TargetActor->GetActorLocation(), Owner->GetStats(EStatsType::ATTACK_DIST));
}

void AAllMonsterController::AttackTarget()
{
	Owner->PlayAttack();
}