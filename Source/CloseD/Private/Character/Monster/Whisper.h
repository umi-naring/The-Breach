// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Monster/MonsterBase.h"
#include "Whisper.generated.h"

UCLASS()
class AWhisper : public AMonsterBase
{
	GENERATED_BODY()
protected:

protected:
	AWhisper();
	virtual void Tick(float DeltaTime) override;

};
