#include "Unit/Manager/UnitManagerComponent.h"

UUnitManagerComponent::UUnitManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UUnitManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


// Called every frame
void UUnitManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

