// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "System/SelectableInterface.h"
#include "GameFramework/Character.h"

#include "Unit/UnitBase.h"

#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
private://변수
	TArray<AActor*> AllSelectable;

public:
	//마우스 드래그
	bool bIsDragging = false;
	bool bIsClick = false;
	bool bTakeOffMouse = false;

	float DragThreshold = 8.f; // 픽셀 기준

	FVector2D DragStart;
	FVector2D DragEnd;

	FVector2D MouseDownPos;

	TArray<AActor*> SelectableActors;
private ://함수
	AMyPlayerController();

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;

	void OnLeftMouseUp();
	void OnLeftMouseDown();

	void SelectSingleUnit();

	//마우스 드래그

	void SelectUnitOnDrag();//드래그 내 유닛들

	void UnitMoveToLocation();//드래그 된 유닛들 움직이기

	void OffCircleDecal();
public:
	void OnUnitHoverBegin(AUnitBase* Unit);
	void OffUnitHoverBegin(AUnitBase* Unit);
};
