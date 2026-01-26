// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MonsterDataSubsystem.generated.h"

class ASpawner;
class AMonsterBase;

USTRUCT(BlueprintType)
struct FMonsterInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AMonsterBase> MonsterClass;

	UPROPERTY(EditAnywhere, Category = "Info")
	float Max_Hp;//최대 체력

	UPROPERTY(EditAnywhere, Category = "Info")
	float Attack;//공격력
	UPROPERTY(EditAnywhere, Category = "Info")
	float Defense;//방어력

	UPROPERTY(EditAnywhere, Category = "Info")
	float Penetration;//방어력 관통

	UPROPERTY(EditAnywhere, Category = "Info")
	float AttackDist;//공격 사거리

	UPROPERTY(EditAnywhere, Category = "Info")
	float RecognizeDist;//인식 사거리

	UPROPERTY(EditAnywhere, Category = "Info")
	float Speed;//속도

	UPROPERTY(EditAnywhere, Category = "Info")
	float RunSpeed;//달리는 속도

	UPROPERTY(EditAnywhere, Category = "Info")
	float EXP;//죽인 말한테 들어가는 경험치

	UPROPERTY(EditAnywhere, Category = "Info")
	float Value;//캐릭터 가치
};

UCLASS()
class UMonsterDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	UDataTable* MonsterTable;

public:
	const FMonsterInfo* GetMonsterInfo(FName MonsterID) const
	{
		return MonsterTable->FindRow<FMonsterInfo>(MonsterID, TEXT("MonsterData"));
	}
};
