// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/GameplayAbility_MeleeWeapon.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Engine/HitResult.h"
#include "Object/BaseWeaponInstance.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"



UGameplayAbility_MeleeWeapon::UGameplayAbility_MeleeWeapon(const FObjectInitializer& Initializer = FObjectInitializer::Get())
{
	
}

ABaseWeaponInstance* UGameplayAbility_MeleeWeapon::GetWeaponInstance()
{
	if(const FGameplayAbilitySpec* Spec = UGameplayAbility::GetCurrentAbilitySpec())
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
	// CommitAbility(Handle,ActorInfo,ActivationInfo);
	//
	// mAbilitySpecHandle = Handle;
	// mActorInfo = ActorInfo;
	// mActivationInfo=ActivationInfo;
	//
	//
	//
	// //Play Attack Montage
	// ActiveMontage();
	//
	// //Wait GameplayEvent 
	// WaitGameplayEventForApplyDamageEffect();
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

/**k
 *	게임플레이이펙트를 타겟에게 적용합니다.
 *	@param Payload : 게임플레이이벤트를 보내주는 BaseWeaponInstance에서 수신하는 데이터입니다.
 */
void UGameplayAbility_MeleeWeapon::ApplyGameplayDamageEffect(FGameplayEventData Payload)
{
	AActor* TargetActor = const_cast<AActor*>(Payload.Target.Get());
	UAbilitySystemComponent* TargetAbilityComp = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);

	if(!TargetAbilityComp)
		return;
	//const FGameplayAbilityTargetDataHandle TargetDataHandle=UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(TargetActor);

	UAbilitySystemComponent* OwnerActorAbilityComp = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwningActorFromActorInfo());

	ensure(OwnerActorAbilityComp);
	OwnerActorAbilityComp->ApplyGameplayEffectToTarget(DamageGameplayEffectClass.GetDefaultObject(),TargetAbilityComp,0.0f,Payload.ContextHandle);
	
}

void UGameplayAbility_MeleeWeapon::SetHitResult(const FHitResult& HitResult)
{
	mHitResult=HitResult;
}

void UGameplayAbility_MeleeWeapon::ActiveMontage()
{
	check(MontageToPlay)
	UAbilityTask_PlayMontageAndWait* MontageProxy=UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this,FName("None"),MontageToPlay);
	MontageProxy->OnCancelled.AddDynamic(this,&UGameplayAbility_MeleeWeapon::AbilityFinish);
	MontageProxy->OnCompleted.AddDynamic(this,&UGameplayAbility_MeleeWeapon::AbilityFinish);
	MontageProxy->OnInterrupted.AddDynamic(this,&UGameplayAbility_MeleeWeapon::AbilityFinish);
	MontageProxy->OnBlendOut.AddDynamic(this,&UGameplayAbility_MeleeWeapon::AbilityFinish);
	MontageProxy->Activate();
}

void UGameplayAbility_MeleeWeapon::WaitGameplayEventForApplyDamageEffect()
{
	UAbilityTask_WaitGameplayEvent* WaitGameplayEvent=UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this,FGameplayTag::RequestGameplayTag("Ability.Attack.Melee"),nullptr,true,true);
	WaitGameplayEvent->EventReceived.AddDynamic(this,&UGameplayAbility_MeleeWeapon::ApplyGameplayDamageEffect);
	WaitGameplayEvent->Activate();
}
