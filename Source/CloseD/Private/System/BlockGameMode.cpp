// Fill out your copyright notice in the Description page of Project Settings.


#include "System/BlockGameMode.h"
#include "Player/PlayerCamera.h"
#include "Player/MyPlayerController.h"

ABlockGameMode::ABlockGameMode()
{
	DefaultPawnClass = APlayerCamera::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
}

float ABlockGameMode::GetCalculate(float A_Attack, float A_Penetration, float B_Defense) 
{ 
	return A_Attack * (1 / (1 + (B_Defense * (100 - A_Penetration / 100)))); 
}