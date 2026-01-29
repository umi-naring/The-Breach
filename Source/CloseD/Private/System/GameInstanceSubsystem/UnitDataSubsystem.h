// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UnitDataSubsystem.generated.h"

class AUnitBase;

USTRUCT(BlueprintType)
struct FUnitInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AUnitBase> UnitClass;

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	float Max_Hp;//최대 체력

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	float Attack;//공격력

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	float Defense;//방어력

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	float Penetration;//방어력 관통

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	float AttackDist;//공격 사거리

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	float RecognizeDist;//인식 사거리

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	float Speed;//속도

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	float RunSpeed;//달리는 속도

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float Max_EXP;//현재 레벨에서의 최대 경험치

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	float Value;//캐릭터 가치
};

UCLASS()
class UUnitDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
};
