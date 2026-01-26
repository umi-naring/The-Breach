// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MonsterManagerComponent.generated.h"

class ASpawner;
class AMonsterBase;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UMonsterManagerComponent : public UActorComponent
{
	GENERATED_BODY()

private:/*
	UPROPERTY(EditDefaultsOnly, Category = "Info")
	TMap<TSubclassOf<AMonsterBase>, FMonsterSpawnInfo> MonsterInfo;

	FMonsterSpawnInfo MInfo;*/


private:/*
	void SpawnMonster();
	void SetSpawnerInfo(ASpawner* Spawner, FMonsterSpawnInfo& Info);*/

public:
	// Sets default values for this component's properties
	UMonsterManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};