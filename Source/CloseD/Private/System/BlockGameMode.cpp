// Fill out your copyright notice in the Description page of Project Settings.


#include "System/BlockGameMode.h"
#include "Player/PlayerCamera.h"
#include "Player/MyPlayerController.h"

#include "Kismet/GameplayStatics.h"

#include "Nexus.h"

ABlockGameMode::ABlockGameMode()
{
	DefaultPawnClass = APlayerCamera::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();

}

float ABlockGameMode::GetCalculate(float A_Attack, float A_Penetration, float B_Defense) 
{ 
	return A_Attack * (1 / (1 + (B_Defense * (100 - A_Penetration / 100)))); 
}

AActor* ABlockGameMode::GetNexus()
{
	TArray<AActor*> Found;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANexus::StaticClass(), Found);

	if (Found.Num() == 0)
		return nullptr;

	return Found[0];
}

bool ABlockGameMode::TryConsumeWaveCost(int Cost)
{
	if (_remainCost < Cost)
		return false;

	_remainCost -= Cost;
	return true;
}