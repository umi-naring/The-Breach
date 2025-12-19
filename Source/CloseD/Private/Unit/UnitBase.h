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
	void SelectedCircleDecalVisibility(bool DragSelected);
	void SelectedDecalVisibility(bool Visible);
};
