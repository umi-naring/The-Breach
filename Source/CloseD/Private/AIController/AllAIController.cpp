// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController/AllAIController.h"

AAllAIController::AAllAIController()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AAllAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Owner = Cast<AMonsterBase>(GetPawn());

	if (Behavior)
		RunBehaviorTree(Behavior);

	BBComp = GetBlackboardComponent();

	BBComp->SetValueAsInt("TargetUnit", 0);
	BBComp->SetValueAsInt("TargetNexus", 0);
}

void AAllAIController::AttackTarget(AUnitBase* HitActor)
{
	ABlockGameMode* GameMode = Cast<ABlockGameMode>(GetWorld()->GetAuthGameMode());

	float AIAttack = Owner->GetDamage();
	float AIPenetration = Owner->GetPenetration();

	float UnitDefense = HitActor->GetDefense();

	float Damage = GameMode->GetCalculate(AIAttack, AIPenetration, UnitDefense);

	UGameplayStatics::ApplyDamage(HitActor, Damage, HitActor->GetInstigatorController(), HitActor, NULL);
}
