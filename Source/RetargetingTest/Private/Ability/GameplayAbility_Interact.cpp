// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/GameplayAbility_Interact.h"

UGameplayAbility_Interact::UGameplayAbility_Interact(const FObjectInitializer& ObjectInitializer)
{
	//ActivationPolicy = EGameAbilityActivationPolicy::OnSpawn;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
}

void UGameplayAbility_Interact::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}
