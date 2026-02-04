// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Monster/MonsterAIController/AllMonsterController.h"

#include "System/BlockGameMode.h"

AAllMonsterController::AAllMonsterController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAllMonsterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	InitSetting();
}

void AAllMonsterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!Owner || Owner->IsAttacking || Owner->IsAttackMontagePlaying())
		return;

	if (IsInAttackRange())
		Owner->PlayAttack();
}

void AAllMonsterController::InitSetting()
{
	Owner = Cast<AMonsterBase>(GetPawn());

	AActor* Nexus = Cast<ABlockGameMode>(
		GetWorld()->GetAuthGameMode()
	)->GetNexus();

	Owner->RequestSetTarget(Nexus);
}

void AAllMonsterController::RequestMoveToTarget(AActor* InTarget)
{
	if (!InTarget || !Owner) return;

	ExecuteMove(InTarget);
}

void AAllMonsterController::ExecuteMove(AActor* Target)
{
	if (Owner->GetStats(EStatsType::ATTACK_DIST) <= 0)
		MoveToActor(
			Target, 
			30.f
		);
	else
		MoveToActor(
			Target,
			Owner->GetStats(EStatsType::ATTACK_DIST)
		);
}