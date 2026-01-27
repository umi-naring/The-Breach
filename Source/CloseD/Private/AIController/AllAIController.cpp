// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController/AllAIController.h"

#include "System/BlockGameMode.h"

#include "Monster/MonsterBase.h"
#include "Unit/UnitBase.h"


AAllAIController::AAllAIController()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AAllAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Owner = Cast<AMonsterBase>(GetPawn());
}

void AAllAIController::InitNexusTarget()
{
	TargetActor = Cast<ABlockGameMode>(GetWorld()->GetAuthGameMode())->GetNexus();
}

void AAllAIController::MoveToTarget()
{
	MoveToLocation(TargetActor->GetActorLocation(), Owner->GetStats(EStatsType::ATTACK_DIST));
}

void AAllAIController::AttackTarget()
{
	Owner->PlayAttackMontage();
}