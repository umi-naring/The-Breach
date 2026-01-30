// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Monster/Whisper.h"

AWhisper::AWhisper()
{
	PrimaryActorTick.bCanEverTick = true;
	CanSkill = false;
}

void AWhisper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

