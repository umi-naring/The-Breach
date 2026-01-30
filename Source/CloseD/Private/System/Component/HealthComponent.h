// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDamaged, float, Damage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDead);

class ACharacterBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	float Max_HP;
	float Current_HP;

	UPROPERTY(BlueprintAssignable)
	FOnDamaged OnDamaged;
	UPROPERTY(BlueprintAssignable)
	FOnDead OnDead;

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetHP(float MaxHealth);

	UFUNCTION()
	void OnTakeDamage(float Damage);
};
