// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Nexus.generated.h"

class UHealthComponent;

UCLASS()
class ANexus : public AActor
{
	GENERATED_BODY()
private:
	UHealthComponent* HealthComponent;

public:	
	// Sets default values for this actor's properties
	ANexus();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
