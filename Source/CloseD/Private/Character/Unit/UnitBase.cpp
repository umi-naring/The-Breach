// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Unit/UnitBase.h"

#include "Character/Unit/UnitAIController/AllUnitController.h"
#include "Player/MyPlayerController.h"

#include "Character/Monster/MonsterBase.h"

// Sets default values
AUnitBase::AUnitBase()
{
	// 틱 비활성화
	PrimaryActorTick.bCanEverTick = false;

	Current_HP = 0.f;

	// 데칼 설정
	SetDecal();
}

void AUnitBase::SetDecal()
{
	// 선택 원 데칼
	SelectedCircleDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("SelectedCircleDecal"));
	SelectedCircleDecal->SetupAttachment(RootComponent);

	// 선택 데칼
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

	// Controller 초기화
	InitController();

	InitAttackSphere();

	// 공격 스피어 오버랩 이벤트 바인딩
	
}

void AUnitBase::InitAttackSphere()
{
	if (AttackSphere)
		AttackSphere->SetSphereRadius(GetAttackRange());
}

// Called every frame
void AUnitBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Controller 초기화
void AUnitBase::InitController()
{
	UnitController = Cast<AAllUnitController>(GetController());
}

// 선택 원 데칼 보이기/숨기기
void AUnitBase::SelectedCircleDecalVisibility(bool DragSelected)
{
	//UE_LOG(LogTemp, Warning, TEXT("Name : %s, bool : %d"), *GetName(), DragSelected)

	if (!SelectedDecal)
		return;

	if (DragSelected)
		SelectedCircleDecal->SetVisibility(true);
	else
		SelectedCircleDecal->SetVisibility(false);
}

// 마우스 커서가 액터 위에 있을 때 호출
void AUnitBase::NotifyActorBeginCursorOver()
{
	Super::NotifyActorBeginCursorOver();

	if (SelectedDecal)
		SelectedDecalVisibility(true);

	if (PC)
		PC->OnUnitHoverBegin(this);
}

// 마우스 커서가 액터에서 벗어날 때 호출
void AUnitBase::NotifyActorEndCursorOver()
{
	Super::NotifyActorEndCursorOver();

	if (SelectedDecal)
		SelectedDecalVisibility(false);

	if (PC)
		PC->OffUnitHoverBegin(this);
}

// 선택 된 데칼 보이기/숨기기
void AUnitBase::SelectedDecalVisibility(bool Visible)
{
	SelectedDecal->SetVisibility(Visible);
}

// 움직이게 하는 함수
void AUnitBase::TakeMove(FVector SendLocation)
{
	if (!UnitController)
		return;

	UnitController->UnitMoveToLocation(SendLocation);
}


// 공격 재생
void AUnitBase::PlayAttack()
{
    if (!Attack_Montage)
    {
        IsAttacking = false;
        return;
    }

    UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
    if (!AnimInstance)
        return;

    if (AnimInstance->Montage_IsPlaying(Attack_Montage))
        return;

    IsAttacking = true;

    FOnMontageEnded EndDelegate;
    EndDelegate.BindUObject(this, &AUnitBase::OnAttackMontageEnded);
    AnimInstance->Montage_SetEndDelegate(EndDelegate, Attack_Montage);

    AttackComp->Attack(EAttackType::Normal);
}

// 공격 멈춤
void AUnitBase::StopAttack()
{
    IsAttacking = false;

    if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
    {
        if (Attack_Montage && AnimInstance->Montage_IsPlaying(Attack_Montage))
            AnimInstance->Montage_Stop(0.1f, Attack_Montage);
    }
}

// 몽타주 재생 중인지 확인
bool AUnitBase::IsAttackMontagePlaying() const
{
    if (!Attack_Montage)
        return false;

    if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
        return AnimInstance->Montage_IsPlaying(Attack_Montage);

    return false;
}

// 몽타주 종료 콜백
void AUnitBase::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
    if (Montage != Attack_Montage)
        return;

    IsAttacking = false;
}