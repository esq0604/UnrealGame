// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/GameplayAbility_MeleeWeapon.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Engine/HitResult.h"
#include "Weapon/BaseWeaponInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayTag.h"



UGameplayAbility_MeleeWeapon::UGameplayAbility_MeleeWeapon(const FObjectInitializer& ObjectInitializer)
{
	
}

ABaseWeaponInstance* UGameplayAbility_MeleeWeapon::GetWeaponInstance()
{
	if(FGameplayAbilitySpec* Spec = UGameplayAbility::GetCurrentAbilitySpec())
	{
		return Cast<ABaseWeaponInstance>(Spec->SourceObject.Get());
	}
	return nullptr;
}

void UGameplayAbility_MeleeWeapon::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	mAbilitySpecHandle = Handle;
	mActorInfo = ActorInfo;
	mActivationInfo=ActivationInfo;
	
	CommitAbility(Handle,ActorInfo,ActivationInfo);
	
	//UAbilityTask_PlayMontageAndWait::OnCancelled.Add(EndAbility(Handle,ActorInfo,ActivationInfo,true,true));
	UAbilityTask_PlayMontageAndWait MontageProxy;
	MontageProxy.CreatePlayMontageAndWaitProxy(this,FName("None"),MontageToPlay);
	MontageProxy.OnCancelled.AddDynamic(this,&UGameplayAbility_MeleeWeapon::AbilityFinish);
	MontageProxy.OnCompleted.AddDynamic(this,&UGameplayAbility_MeleeWeapon::AbilityFinish);
	MontageProxy.OnInterrupted.AddDynamic(this,&UGameplayAbility_MeleeWeapon::AbilityFinish);
	MontageProxy.OnBlendOut.AddDynamic(this,&UGameplayAbility_MeleeWeapon::AbilityFinish);
	MontageProxy.Activate();
}

void UGameplayAbility_MeleeWeapon::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGameplayAbility_MeleeWeapon::AbilityFinish()
{
	EndAbility(mAbilitySpecHandle,mActorInfo,mActivationInfo,true,false);
}



