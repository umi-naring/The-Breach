// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Monster/MonsterAIController/AllMonsterController.h"

#include "System/BlockGameMode.h"

AAllMonsterController::AAllMonsterController()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AAllMonsterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	InitSetting();

	// 공격 체크 타이머 시작
	GetWorldTimerManager().SetTimer(
		AttackCheckTimer,
		this,
		&AAllMonsterController::AttackCheck,
		0.2f,   // 0.2~0.3초면 충분
		true
	);
}

void AAllMonsterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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

void AAllMonsterController::AttackCheck()
{
	if (!Owner)
		return;

	if (Owner->IsAttacking)//몬스터가 공격 중일 경우
	{
		// 공격 범위를 벗어나면 공격 중지 후 이동
		if (!IsInAttackRange())
		{
			Owner->StopAttack();
			if (Owner->GetCurrentTarget())
				RequestMoveToTarget(Owner->GetCurrentTarget());
		}
		return;
	}	
	
	if (Owner->IsAttackMontagePlaying())
		return;

	// 공격 범위 내에 타겟이 있으면 공격, 없으면 이동
	if (IsInAttackRange())
	{
		Owner->PlayAttack();
	}
}
