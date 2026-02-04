// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Monster/MonsterBase.h"

#include "Character/Monster/MonsterAIController/AllMonsterController.h"

#include "System/Component/HealthComponent.h"
#include "System/Component/AttackComponent.h"
#include "System/BlockGameMode.h"

#include "Character/Unit/UnitBase.h"

AMonsterBase::AMonsterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	RecognizeSphere = CreateDefaultSubobject<USphereComponent>(TEXT("RecognizeSphere"));
	RecognizeSphere->SetupAttachment(RootComponent);
	RecognizeSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	RecognizeSphere->SetCollisionObjectType(ECC_WorldDynamic);
	RecognizeSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	RecognizeSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RecognizeSphere->SetSphereRadius(0.f);
}

void AMonsterBase::BeginPlay()
{
	Super::BeginPlay();

	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	if (ABlockGameMode* GM = Cast<ABlockGameMode>(GetWorld()->GetAuthGameMode()))
		NexusTarget = GM->GetNexus();

	if (RecognizeSphere)
	{
		RecognizeSphere->OnComponentBeginOverlap.AddDynamic(this, &AMonsterBase::OnRecognizeBeginOverlap);
		RecognizeSphere->OnComponentEndOverlap.AddDynamic(this, &AMonsterBase::OnRecognizeEndOverlap);
	}

	InitMovementState();
}

void AMonsterBase::InitMovementState()
{
	GetWorldTimerManager().SetTimer(
		MovementStateTimer,
		this,
		&AMonsterBase::UpdateMovementState,
		0.2f,   // 0.2~0.3초면 충분
		true
	);
}

void AMonsterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	Controller = Cast<AAllMonsterController>(GetController());

	SetTarget_Internal(NexusTarget);

	FTimerHandle DelayMove;

	//임시(나중에는 스포너에서 호출 예정), 디버그 모드로 놓을 예정
	GetWorld()->GetTimerManager().SetTimer(DelayMove, [this]() {
		if (Controller)
			Controller->RequestMoveToTarget(CurrentTarget);
		}, 0.5f, false);
	
}

void AMonsterBase::InitInfo(EStatsType Type, float _statValue)
{
	Stats.Add(Type, _statValue);
 
	OnStatEvent(Type);
}

void AMonsterBase::OnStatEvent(EStatsType Type)
{
	switch (Type)
	{
		case EStatsType::HP:
			HealthComp->SetHP(GetStats(EStatsType::HP));
			break;

		case EStatsType::SPEED:
			SetSpeed();
			break;

		case EStatsType::RECOGNIZE_DIST:
			if (RecognizeSphere)
				RecognizeSphere->SetSphereRadius(GetStats(EStatsType::RECOGNIZE_DIST));
			break;

		default:
			break;
	}
}

void AMonsterBase::PlayAttack()
{
	if (!Attack_Montage)
	{
		IsAttacking = false;
		SetSpeed();
		return;
	}

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (!AnimInstance)
		return;

	if (AnimInstance->Montage_IsPlaying(Attack_Montage))
		return;

	IsAttacking = true;
	SetSpeed();

	if (Controller)
		Controller->StopMovement();

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &AMonsterBase::OnAttackMontageEnded);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, Attack_Montage);

	AttackComp->Attack(EAttackType::Normal);
}

void AMonsterBase::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage != Attack_Montage)
		return;

	OnAttackFinished();
}

void AMonsterBase::OnAttackFinished()
{
	IsAttacking = false;

	if (!Controller || !CurrentTarget)
		return;

	if (!IsAttacking && Controller->IsInAttackRange())
		PlayAttack();
	else
	{
		SetSpeed();
		Controller->RequestMoveToTarget(CurrentTarget);
	}
}

void AMonsterBase::SetSpeed()
{
	float NewSpeed = 0.f;

	if (IsAttacking)
		NewSpeed = 0.f;
	else if (IsRun)
		NewSpeed = MonsterInfo.RunSpeed;
	else
		NewSpeed = MonsterInfo.Speed;

	GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
}

void AMonsterBase::OnUnitBeginOverlap(AActor* OtherActor)
{
	AUnitBase* Unit = Cast<AUnitBase>(OtherActor);
	if (!Unit)
		return;

	OverlappingUnits.Add(Unit);

	if (CurrentTarget == nullptr || CurrentTarget == NexusTarget)
	{
		AUnitBase* Closest = GetClosestOverlappingUnit();
		if (Closest)
			SetTarget_Internal(Closest);
	}
}

void AMonsterBase::OnUnitEndOverlap(AActor* OtherActor)
{
	AUnitBase* Unit = Cast<AUnitBase>(OtherActor);
	if (!Unit)
		return;

	OverlappingUnits.Remove(Unit);

	if (OtherActor != CurrentTarget)
		return;

	AUnitBase* Closest = GetClosestOverlappingUnit();
	if (Closest)
		SetTarget_Internal(Closest);
	else
		SetTarget_Internal(NexusTarget);
}

void AMonsterBase::OnTargetUnitDead()
{
	SetTarget_Internal(NexusTarget);
}

bool AMonsterBase::CanChangeTarget(AActor* NewTarget) const
{
	// 초기 상태
	if (CurrentTarget == nullptr)
		return true;

	// 이미 같은 타겟
	if (CurrentTarget == NewTarget)
		return false;

	// 유닛 타겟 중일 때
	if (CurrentTarget != NexusTarget)
		return NewTarget == NexusTarget;

	return true;
}

void AMonsterBase::RequestSetTarget(AActor* NewTarget)
{
	if (!NewTarget) return;

	if (!CanChangeTarget(NewTarget)) return;

	SetTarget_Internal(NewTarget);
}

void AMonsterBase::SetTarget_Internal(AActor* NewTarget)
{
	if (CurrentTarget == NewTarget)
		return;

	CurrentTarget = NewTarget;

	UpdateMovementState();

	if (Controller)
	{
		if (CurrentTarget)
			Controller->SetFocus(CurrentTarget);
		else
			Controller->ClearFocus(EAIFocusPriority::Gameplay);

		Controller->RequestMoveToTarget(CurrentTarget);
	}
}

void AMonsterBase::UpdateMovementState()
{
	if (!Controller || !CurrentTarget)
		return;

	bool bShouldRun = Controller->IsInRecognizeRange(CurrentTarget);

	if (IsRun != bShouldRun)
	{
		IsRun = bShouldRun;
		SetSpeed();
	}
}

void AMonsterBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorldTimerManager().ClearTimer(MovementStateTimer);
	Super::EndPlay(EndPlayReason);
}

void AMonsterBase::OnRecognizeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnUnitBeginOverlap(OtherActor);
}

void AMonsterBase::OnRecognizeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OnUnitEndOverlap(OtherActor);
}

AUnitBase* AMonsterBase::GetClosestOverlappingUnit() const
{
	AUnitBase* Closest = nullptr;
	float BestDistSq = TNumericLimits<float>::Max();

	for (AUnitBase* Unit : OverlappingUnits)
	{
		if (!IsValid(Unit))
			continue;

		const float DistSq = FVector::DistSquared(GetActorLocation(), Unit->GetActorLocation());
		if (DistSq < BestDistSq)
		{
			BestDistSq = DistSq;
			Closest = Unit;
		}
	}

	return Closest;
}

bool AMonsterBase::IsAttackMontagePlaying() const
{
	if (!Attack_Montage)
		return false;

	if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
		return AnimInstance->Montage_IsPlaying(Attack_Montage);

	return false;
}