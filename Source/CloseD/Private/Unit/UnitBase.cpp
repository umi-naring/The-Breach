// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit/UnitBase.h"

#include "Unit/UnitController/AllUnitController.h"
#include "Player/MyPlayerController.h"

// Sets default values
AUnitBase::AUnitBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SelectedCircleDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("SelectedCircleDecal"));
	SelectedCircleDecal->SetupAttachment(RootComponent);

	SelectedDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("SelectionDecal"));
	SelectedDecal->SetupAttachment(RootComponent);

	// 기본은 안 보이게
	SelectedCircleDecal->SetVisibility(false);
	SelectedDecal->SetVisibility(false);

	// 크기 (원 크기)
	SelectedCircleDecal->DecalSize = FVector(32.f, 64.f, 64.f);

	// 바닥에 깔리게 회전
	SelectedCircleDecal->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));

}

// Called when the game starts or when spawned
void AUnitBase::BeginPlay()
{
	Super::BeginPlay();
	
	PC = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());

	LV = 1;
}

// Called every frame
void AUnitBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUnitBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AUnitBase::TakeMove(FVector SendLocation)
{
	AAllUnitController* UnitController = Cast<AAllUnitController>(GetController());
	if (!UnitController)
		return;
	UnitController->UnitMoveToLocation(SendLocation);
}

void AUnitBase::SelectedCircleDecalVisibility(bool DragSelected)
{
	UE_LOG(LogTemp, Warning, TEXT("Name : %s, bool : %d"), *GetName(), DragSelected)

	if (!SelectedDecal)
			return;

	if (DragSelected)
		SelectedCircleDecal->SetVisibility(true);
	else
		SelectedCircleDecal->SetVisibility(false);
}

void AUnitBase::NotifyActorBeginCursorOver()
{
	Super::NotifyActorBeginCursorOver();

	if(SelectedDecal)
		SelectedDecalVisibility(true);

	if (PC)
		PC->OnUnitHoverBegin(this);
}

void AUnitBase::NotifyActorEndCursorOver()
{
	Super::NotifyActorEndCursorOver();

	if (SelectedDecal)
		SelectedDecalVisibility(false);

	if (PC)
		PC->OffUnitHoverBegin(this);
}

void AUnitBase::SelectedDecalVisibility(bool Visible)
{
	SelectedDecal->SetVisibility(Visible);
}

float AUnitBase::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCursor)
{
	const float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCursor);

	if (Damage < 0)
		return 0;

	Current_HP -= Damage;

	if (Current_HP <= 0)
		this->Destroy();

	return Damage;
}

float AUnitBase::GetDefense() { return Defense; }