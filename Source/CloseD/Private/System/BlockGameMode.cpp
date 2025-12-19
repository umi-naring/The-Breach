// Fill out your copyright notice in the Description page of Project Settings.


#include "System/BlockGameMode.h"
#include "Player/PlayerCamera.h"
#include "Player/MyPlayerController.h"

ABlockGameMode::ABlockGameMode()
{
	DefaultPawnClass = APlayerCamera::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
}