// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MonsterManagerComponent.generated.h"

class AMonsterBase;

USTRUCT(BlueprintType)
struct FMonsterSpawnInfo
{
	GENERATED_BODY()

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

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	float EXP;//죽인 말한테 들어가는 경험치
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UMonsterManagerComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Info")
	TMap<TSubclassOf<AMonsterBase>, FMonsterSpawnInfo> MonsterInfo;

	FMonsterSpawnInfo MInfo;

private:
	void SpawnMonster();
	void SetMonsterInfo(AMonsterBase* SpawnMonster);

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
