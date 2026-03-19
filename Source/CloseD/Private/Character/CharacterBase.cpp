// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	AttackSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AttackSphere"));
	AttackSphere->SetupAttachment(RootComponent);
	AttackSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	AttackSphere->SetCollisionObjectType(ECC_WorldDynamic);
	AttackSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	AttackSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	AttackComp = CreateDefaultSubobject<UAttackComponent>(TEXT("Attack"));
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle DelayTimer;

	GetWorldTimerManager().SetTimer(DelayTimer, [this]()
	{
		SettingBind();
	}, 
	0.2f, 
	false);
}

void ACharacterBase::SettingBind()
{
	if (HealthComp)
		HealthComp->OnDeadEvent().AddDynamic(this, &ACharacterBase::OnDead);

	if (AttackSphere)
	{
		AttackSphere->OnComponentBeginOverlap.AddDynamic(this, &ACharacterBase::OnTargetBegin);
		AttackSphere->OnComponentEndOverlap.AddDynamic(this, &ACharacterBase::OnTargetEnd);
	}
}
// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACharacterBase::ApplyDamage(float Damage)
{
	if (HealthComp && !bIsDead)
		HealthComp->OnTakeDamage(Damage);
}

float ACharacterBase::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	ApplyDamage(DamageAmount);
	return DamageAmount;
}

void ACharacterBase::OnDead()
{
	if (bIsDead)
		return;

	bIsDead = true;

	if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
		MoveComp->StopMovementImmediately();

	if (UCapsuleComponent* Capsule = GetCapsuleComponent())
		Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (Death_Montage)
		PlayAnimMontage(Death_Montage);

	SetLifeSpan(2.f);
}

void ACharacterBase::OnTargetBegin(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		TargetInAttackRange.Add(OtherActor);
	}
}

void ACharacterBase::OnTargetEnd(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		TargetInAttackRange.Remove(OtherActor);
	}
}
