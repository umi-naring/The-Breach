// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/MonsterBase.h"

#include "AIController/AllAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackBoardComponent.h"

#include "Whisper.generated.h"

/**
 * 
 */
UCLASS()
class AWhisper : public AMonsterBase
{
	GENERATED_BODY()
protected:

protected:
	AWhisper();
	virtual void Tick(float DeltaTime) override;

};
