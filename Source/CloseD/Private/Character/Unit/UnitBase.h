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

UCLASS()
class AUnitBase : public ACharacterBase, public ISelectableInterface
{
	GENERATED_BODY()
private:
	class AMyPlayerController* PC;

protected:
	float LV;//현 레벨
	float Current_HP;
	float Current_EXP;//현재 경험치
	
	TMap<EStatType, float> Stats;

public:
	bool Selected;

	FUnitInfo* UnitInfo;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UDecalComponent* SelectedCircleDecal;//선택 했을 때 바닥에 뜨는 원

	UPROPERTY(VisibleAnywhere)
	UDecalComponent* SelectedDecal;//선택 했을 때 바뀌는 머테리얼

private:
	virtual void NotifyActorBeginCursorOver() override;
	virtual void NotifyActorEndCursorOver() override;

public:	
	AUnitBase();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Move
	void TakeMove(FVector SendLocation);//컨트롤러한테 움직이게 하라고 명령하는 함수

	void SelectedCircleDecalVisibility(bool DragSelected);// 선택 데칼
	void SelectedDecalVisibility(bool Visible);// 선택 될 캐릭터를 보여주는 데칼

	// Attack
	void PlayAttack();

	// 대미지 입는 함수
	virtual float TakeDamage(
		float DamageAmount, 
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCursor
	) override;

	//float GetStats(EStatsType StatType) const;
};
