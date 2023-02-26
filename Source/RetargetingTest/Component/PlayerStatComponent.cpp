// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatComponent.h"


// Sets default values for this component's properties
UPlayerStatComponent::UPlayerStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

float UPlayerStatComponent::GetAttackDamage()
{
	return AttackDamage;
}

// Called when the game starts
void UPlayerStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerStatComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerStatComponent::SetHP(const float& NewHP)
{
	CurrentHP=NewHP;
	OnHPChanged.Broadcast();
	if(CurrentHP<KINDA_SMALL_NUMBER)
	{
		CurrentHP =0.0f;
		OnHPIsZero.Broadcast();
	}
}

float UPlayerStatComponent::GetHPRatio()
{
	return (MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentHP / MaxHP); 
}


void UPlayerStatComponent::GetDamaged(const float& Damage)
{
	SetHP(FMath::Clamp<float>(CurrentHP-Damage,0.0f,MaxHP));
}
