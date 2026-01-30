// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AllController.generated.h"

class ACharacterBase;

UCLASS()
class AAllController : public AAIController
{
	GENERATED_BODY()
	
protected:
	AActor* TargetActor;
};
