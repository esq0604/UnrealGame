// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/BasePlayerStatComponent.h"

#include "BehaviorTree/Blackboard/BlackboardKeyType.h"


// Sets default values for this component's properties
UBasePlayerStatComponent::UBasePlayerStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	UE_LOG(LogTemp,Warning,TEXT("PlayerStatComponent Constructor "));
	PrimaryComponentTick.bCanEverTick = true;
	AttackDamage=10.0f;
	MaxHp=100.0f;
	NewHpPercent=1;
	CurrentHp=MaxHp;
}

void UBasePlayerStatComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(CurrentStamina<MaxStamina)
	{
		CurrentStamina+=StaminaRegenerateValue;
		SetStamina(CurrentStamina);
	}
}
void UBasePlayerStatComponent::SetStamina(float NewStamina)
{
	CurrentStamina=NewStamina;
	CurStaminaPercent=GetCalculateStaminaRatio(CurrentStamina);
	OnStaminaChangedDelegate.Broadcast();
	UE_LOG(LogTemp,Warning,TEXT("Current Stamina : %f"),CurrentStamina);
}

float UBasePlayerStatComponent::GetCurrentStamina() const
{
	return CurrentStamina;
}

float UBasePlayerStatComponent::GetCurrentStaminaPercent() const
{
	return CurStaminaPercent;
}

float UBasePlayerStatComponent::GetCalculateStaminaRatio(float ChangedStamina) const
{
	return (MaxHp < KINDA_SMALL_NUMBER) ? 0.0f : (ChangedStamina / MaxStamina); 

}








