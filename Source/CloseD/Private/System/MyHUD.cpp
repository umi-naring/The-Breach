// Fill out your copyright notice in the Description page of Project Settings.


#include "System/MyHUD.h"
#include "Player/MyPlayerController.h"

void AMyHUD::DrawHUD()
{
    Super::DrawHUD();

    AMyPlayerController* PC = Cast<AMyPlayerController>(GetOwningPlayerController());
    if (!PC || !PC->bIsDragging)
        return;

    FVector2D CurrentMouse;
    PC->GetMousePosition(CurrentMouse.X, CurrentMouse.Y);

    FVector2D Start = PC->DragStart;
    FVector2D Size = CurrentMouse - Start;

    DrawRect(
        FLinearColor(0, 1, 0, 0.15f),
        Start.X,
        Start.Y,
        Size.X,
        Size.Y
    );
}