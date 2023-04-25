// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/Ability/PlayerLightAttackAbility.h"

#include "RetargetingTest/Public/Component/BaseStateManagerComponent.h"
#include "RetargetingTest/Public/State/BaseStateObject.h"


UPlayerLightAttackAbility::UPlayerLightAttackAbility()
{
	AbilityGameplayTag.FromExportString("Ability.LightAttack");
}

void UPlayerLightAttackAbility::StartAbility()
{
	Super::StartAbility();
	AnimMontages = GetAbilityMontage(GetClass());

	PlayAbilityMontage(AnimMontages[ComboAttackIndex++]);
	if(ComboAttackIndex>AnimMontages.Num()-1)
	{
		ComboAttackIndex=0;
	}
}

/**
 * 공격몽타주가 있어야하고, 현재 상태가 걷기, 달리기, 대기 상태여야 공격이 가능합니다.
 */
bool UPlayerLightAttackAbility::CanPerformAbility()
{
	if(GetAbilityMontage(GetClass()).Num()>0)
	{
		const FGameplayTag IdleStateTag = FGameplayTag::RequestGameplayTag("State.Idle");
		const FGameplayTag SprintStateTag = FGameplayTag::RequestGameplayTag("State.Sprint");
		const FGameplayTag WalkStateTag = FGameplayTag::RequestGameplayTag("State.Walk");
		if(StateManagerComponent->GetCurrentActiveState())
		{
			const FGameplayTag CurrentStateTag =StateManagerComponent->GetCurrentActiveState()->GetGameplayTag();
			if(CurrentStateTag==IdleStateTag || CurrentStateTag==SprintStateTag || CurrentStateTag == WalkStateTag)
			{
				return true;
			}
		}
	}
	return false;
}

void UPlayerLightAttackAbility::EndAbility()
{
	Super::EndAbility();
	UE_LOG(LogTemp,Warning,TEXT("LightAttackEndAbility"));
	const FGameplayTag IdleStateTag = FGameplayTag::RequestGameplayTag("State.Idle");
	const UBaseStateObject* LocalIdleState=StateManagerComponent->GetStateOfGameplayTag(IdleStateTag);
	if(LocalIdleState ==nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("EndAbility LocalIdleState nullptr "));

	}
	StateManagerComponent->PerformStateOfClass(LocalIdleState->GetClass());
}
