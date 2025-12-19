// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MyPlayerController.h"
#include "Player/PlayerCamera.h"
#include "Kismet/GameplayStatics.h"

AMyPlayerController::AMyPlayerController()
{
    bShowMouseCursor = true;
    bEnableMouseOverEvents = true;
    bEnableClickEvents = true;
}

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();

}

void AMyPlayerController::PlayerTick(float DeltaTime)
{
    Super::PlayerTick(DeltaTime);

    if (!bIsClick)
        return;

    GetMousePosition(DragEnd.X, DragEnd.Y);

    float Dist = FVector2D::Distance(MouseDownPos, DragEnd);

    if (!bIsDragging && Dist > DragThreshold)
        bIsDragging = true;

    if (bIsDragging)
        SelectUnitOnDrag();
}

void AMyPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindAction("LeftClick", IE_Pressed, this, &AMyPlayerController::OnLeftMouseDown);
    InputComponent->BindAction("LeftClick", IE_Released, this, &AMyPlayerController::OnLeftMouseUp);

    InputComponent->BindAction("RightClick", IE_Pressed, this, &AMyPlayerController::UnitMoveToLocation);
}

void AMyPlayerController::OnLeftMouseDown()
{
    bIsClick = true;
    bIsDragging = false;

    GetMousePosition(MouseDownPos.X, MouseDownPos.Y);

    DragStart = MouseDownPos;
}

void AMyPlayerController::OnLeftMouseUp()
{
    bTakeOffMouse = true;

    if (bIsDragging)
        SelectUnitOnDrag();
    else
        SelectSingleUnit();

    bIsDragging = false;
    bIsClick = false;
}

void AMyPlayerController::UnitMoveToLocation()
{
    FHitResult Hit;
    
    bool bHit = GetHitResultUnderCursor(
        ECC_Visibility,
        false,
        Hit);

    if (!bHit)
        return;

    for (AActor* Unit : SelectableActors)
    {
        AUnitBase* DragUnit = Cast<AUnitBase>(Unit);

        if (DragUnit)
            DragUnit->TakeMove(Hit.Location);
    }
}
void AMyPlayerController::SelectSingleUnit()
{
    SelectableActors.Empty();

    FHitResult Hit;

    bool bHit = GetHitResultUnderCursor(
        ECC_Visibility,
        false,
        Hit
    );

    OffCircleDecal();

    if (!bHit)
        return;

    AUnitBase* Unit = Cast<AUnitBase>(Hit.GetActor());
    if (!Unit)
        return;


    SelectableActors.Add(Unit);
    Unit->SelectedCircleDecalVisibility(true);
}

void AMyPlayerController::SelectUnitOnDrag()
{
    FVector2D Min(
        FMath::Min(DragStart.X, DragEnd.X),
        FMath::Min(DragStart.Y, DragEnd.Y)
    );

    FVector2D Max(
        FMath::Max(DragStart.X, DragEnd.X),
        FMath::Max(DragStart.Y, DragEnd.Y)
    );

    UGameplayStatics::GetAllActorsWithInterface(
        GetWorld(),
        USelectableInterface::StaticClass(),
        AllSelectable
    );

    SelectableActors.Empty();

    for (AActor* Actor : AllSelectable)
    {
        AUnitBase* AllUnit = Cast<AUnitBase>(Actor);

        FVector2D ScreenPos;
        ProjectWorldLocationToScreen(
            Actor->GetActorLocation(),
            ScreenPos
        );

        bool InSide = ScreenPos.X >= Min.X && ScreenPos.X <= Max.X &&
            ScreenPos.Y >= Min.Y && ScreenPos.Y <= Max.Y;

       if (bIsDragging && InSide)
           AllUnit->SelectedDecalVisibility(true);

       else if (bIsDragging && !InSide)
           AllUnit->SelectedDecalVisibility(false);

       if (bTakeOffMouse)
       {
           AllUnit->SelectedDecalVisibility(false); 
           AllUnit->SelectedCircleDecalVisibility(false);

           if (InSide)
           {
               SelectableActors.Add(Actor);
               AllUnit->SelectedCircleDecalVisibility(true);
               ISelectableInterface::Execute_OnSelected(Actor);
           }
       }
       
    }
    bTakeOffMouse = false;
    /*for (AActor* Actor : SelectableActors)
    {
        UE_LOG(LogTemp, Warning, TEXT("TargetText : %s"), *Actor->GetName())
    }*/
}

void AMyPlayerController::OnUnitHoverBegin(AUnitBase* Unit)
{
    CurrentMouseCursor = EMouseCursor::Hand;
}

void AMyPlayerController::OffUnitHoverBegin(AUnitBase* Unit)
{
    CurrentMouseCursor = EMouseCursor::Default;
}

void AMyPlayerController::OffCircleDecal()
{
    UGameplayStatics::GetAllActorsWithInterface(
        GetWorld(),
        USelectableInterface::StaticClass(),
        AllSelectable
    );

    for (AActor* Actor : AllSelectable)
    {
        AUnitBase* AllUnit = Cast<AUnitBase>(Actor);
        AllUnit->SelectedCircleDecalVisibility(false);
    }
}