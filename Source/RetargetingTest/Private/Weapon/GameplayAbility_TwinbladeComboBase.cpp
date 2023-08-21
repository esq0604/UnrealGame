// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/GameplayAbility_TwinbladeComboBase.h"


void UGameplayAbility_TwinbladeComboBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	CommitAbility(Handle,ActorInfo,ActivationInfo);

	mAbilitySpecHandle = Handle;
	mActorInfo = ActorInfo;
	mActivationInfo=ActivationInfo;
	
}
