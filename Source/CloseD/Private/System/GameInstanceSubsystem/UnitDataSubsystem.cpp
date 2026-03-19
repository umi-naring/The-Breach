// Fill out your copyright notice in the Description page of Project Settings.


#include "System/GameInstanceSubsystem/UnitDataSubsystem.h"

#include "Character/Unit/UnitBase.h"

void UUnitDataSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	LoadedUnitTable = UnitTable.IsNull()
		? nullptr
		: UnitTable.LoadSynchronous();
}

void UUnitDataSubsystem::Deinitialize()
{
	Super::Deinitialize();
	LoadedUnitTable = nullptr;
}
