// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Whisper.h"

AWhisper::AWhisper()
{
	PrimaryActorTick.bCanEverTick = true;
	CanSkill = false;
}

void AWhisper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	SetSpeed();
}

void AWhisper::SetSpeed()
{
	AAllAIController* OwnerAIController = Cast<AAllAIController>(GetController());
	if (!OwnerAIController)
		return;

	UBlackboardComponent* BBComp = OwnerAIController->GetBlackboardComponent();
	if (!BBComp)
		return;

	if (BBComp->GetValueAsInt("TargetUnit") == 1)
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	else
		GetCharacterMovement()->MaxWalkSpeed = Speed;
}