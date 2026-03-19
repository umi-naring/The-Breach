// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"

#include "System/GameInstanceSubsystem/UnitDataSubsystem.h"
#include "System/SelectableInterface.h"

#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"

#include "Animation/AnimMontage.h"
 
#include "UnitBase.generated.h"

class AMonsterBase;
class AAllUnitController;

UCLASS()
class CLOSED_API AUnitBase : public ACharacterBase, public ISelectableInterface
{
	GENERATED_BODY()
private:
	class AMyPlayerController* PC;

protected:
	float Current_HP;
	float Current_EXP;//현재 경험치
	
	TMap<EStatType, float> Stats;
	AAllUnitController* UnitController;

public:
	bool Selected;

	FUnitInfo* UnitInfo;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	bool IsAttacking = false;

protected:
	virtual void BeginPlay() override;
	void InitAttackSphere();

	UPROPERTY(VisibleAnywhere)
	UDecalComponent* SelectedCircleDecal;//선택 했을 때 바닥에 뜨는 원

	UPROPERTY(VisibleAnywhere)
	UDecalComponent* SelectedDecal;//선택 했을 때 바뀌는 머테리얼

private:
	virtual void NotifyActorBeginCursorOver() override;
	virtual void NotifyActorEndCursorOver() override;

private:
	void SetDecal();
	void InitController();

public:	
	AUnitBase();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Move
	void TakeMove(FVector SendLocation);//컨트롤러한테 움직이게 하라고 명령하는 함수

	void SelectedCircleDecalVisibility(bool DragSelected);// 선택 데칼
	void SelectedDecalVisibility(bool Visible);// 선택 될 캐릭터를 보여주는 데칼

	// Attack
	void PlayAttack();
	void StopAttack();
	bool IsAttackMontagePlaying() const;

	float GetAttackRange() const
	{
		return UnitInfo ? UnitInfo->AttackDist : 0.f;
	}

	float GetAttackPower() const
	{
		return UnitInfo ? UnitInfo->Attack : 0.f;
	}

private:
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
};
