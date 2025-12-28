// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "System/SelectableInterface.h"

#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"

#include "UnitBase.generated.h"


class UDecalComponent;

UCLASS()
class AUnitBase : public ACharacter, public ISelectableInterface
{
	GENERATED_BODY()
private:
	class AMyPlayerController* PC;

protected:

		float LV;//현 레벨

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
		float Max_Hp;//최대 체력

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
		float Current_HP;//현재 체력

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
		float Attack;//공격력

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
		float Defense;//방어력

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
		float Penetration;//방어력 관통

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
		float Speed;//속도

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
		float Max_EXP;//현재 레벨에서의 최대 경험치

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
		float Current_EXP;//현재 경험치

public:
	// Sets default values for this character's properties
	bool Selected;

protected:
	// Called when the game starts or when spawned
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

	void TakeMove(FVector SendLocation);//컨트롤러한테 움직이게 하라고 명령하는 함수

	void SelectedCircleDecalVisibility(bool DragSelected);// 선택 데칼
	void SelectedDecalVisibility(bool Visible);// 선택 될 캐릭터를 보여주는 데칼

	// 대미지 입는 함수
	virtual float TakeDamage(
		float DamageAmount, 
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCursor
	) override;

	float GetDefense();
};
