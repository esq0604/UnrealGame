// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/GameplayAbility_MeleeWeapon.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Engine/HitResult.h"
#include "Object/BaseWeaponItem.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "GameplayCueFunctionLibrary.h"



UGameplayAbility_MeleeWeapon::UGameplayAbility_MeleeWeapon(const FObjectInitializer& Initializer = FObjectInitializer::Get())
{
	
}

ABaseWeaponItem* UGameplayAbility_MeleeWeapon::GetWeaponInstance()
{
	if(const FGameplayAbilitySpec* Spec = UGameplayAbility::GetCurrentAbilitySpec())
	{
		return Cast<ABaseWeaponItem>(Spec->SourceObject.Get());
	}
	return nullptr;
}

/**
 * @brief 근접무기 어빌리티 활성화시 동작입니다. 몽타주를 실행하고 데미지를 적용하도록합니다.
 */
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
	// if(ensure(AttackMontage))
	// 	ActiveMontage(AttackMontage);
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

void UGameplayAbility_MeleeWeapon::MontageFinish()
{
	UE_LOG(LogTemp,Warning,TEXT("MontageFinish"));
	EndAbility(mAbilitySpecHandle,mActorInfo,mActivationInfo,true,false);
}

void UGameplayAbility_MeleeWeapon::MontageCanceled()
{
	UE_LOG(LogTemp,Warning,TEXT("MontageCancled"));
	EndAbility(mAbilitySpecHandle,mActorInfo,mActivationInfo,true,true);
}

/**k
 *	타겟에게 데미지 이펙트를 전달합니다. 이때 타겟의 상태에 따라 패리, 디펜스를 수행하도록 합니다.
 *	@param Payload : 게임플레이이벤트를 보내주는 BaseWeaponInstance에서 수신하는 데이터입니다.
 */
void UGameplayAbility_MeleeWeapon::ApplyGameplayDamageEffect(FGameplayEventData Payload)
{
	AActor* TargetActor = const_cast<AActor*>(Payload.Target.Get());
	UAbilitySystemComponent* TargetAbilityComp = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor);
	UAbilitySystemComponent* OwnerActorAbilityComp = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwningActorFromActorInfo());
	FGameplayCueParameters Parameters(Payload.ContextHandle);
	UE_LOG(LogTemp,Warning,TEXT("Event Received"));
	if(!TargetAbilityComp)
		return;
	//const FGameplayAbilityTargetDataHandle TargetDataHandle=UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(TargetActor);
	
	if(TargetAbilityComp->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("Ability.Parry")))
	{
		//Target Do Parry;
		FGameplayTag ParryTag = FGameplayTag::RequestGameplayTag("Ability.Parry");
		UGameplayCueFunctionLibrary::ExecuteGameplayCueOnActor(TargetActor,ParryTag,Parameters);
		ActiveMontage(AttackFailMontage);
	}
	else if(TargetAbilityComp->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("Character.IsBlocking")))
	{
		//Target Do Defense
		FGameplayTag DefenseTag = FGameplayTag::RequestGameplayTag("Character.IsBlocking");
		UGameplayCueFunctionLibrary::ExecuteGameplayCueOnActor(TargetActor,DefenseTag,Parameters);
	}
	else
	{
		//Target Get Damage;
		UE_LOG(LogTemp,Warning,TEXT("Target Get Damage"));
		OwnerActorAbilityComp->ApplyGameplayEffectToTarget(DamageGameplayEffectClass.GetDefaultObject(),TargetAbilityComp,0.0f,Payload.ContextHandle);
	}
}

void UGameplayAbility_MeleeWeapon::SetHitResult(const FHitResult& HitResult)
{
	mHitResult=HitResult;
}

void UGameplayAbility_MeleeWeapon::ActiveMontage(UAnimMontage* PlayMontage)
{
	check(PlayMontage)
	UAbilityTask_PlayMontageAndWait* MontageProxy=UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this,FName("None"),PlayMontage);
	MontageProxy->OnCancelled.AddDynamic(this,&UGameplayAbility_MeleeWeapon::MontageCanceled);
	MontageProxy->OnCompleted.AddDynamic(this,&UGameplayAbility_MeleeWeapon::MontageFinish);
	MontageProxy->OnInterrupted.AddDynamic(this,&UGameplayAbility_MeleeWeapon::MontageCanceled);
	MontageProxy->OnBlendOut.AddDynamic(this,&UGameplayAbility_MeleeWeapon::MontageFinish);
	MontageProxy->Activate();
}

void UGameplayAbility_MeleeWeapon::WaitGameplayEventForApplyDamageEffect()
{
	UAbilityTask_WaitGameplayEvent* WaitGameplayEvent=UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this,FGameplayTag::RequestGameplayTag("Ability.Attack.Melee"),nullptr,true,true);
	WaitGameplayEvent->EventReceived.AddDynamic(this,&UGameplayAbility_MeleeWeapon::ApplyGameplayDamageEffect);
	WaitGameplayEvent->Activate();
}
