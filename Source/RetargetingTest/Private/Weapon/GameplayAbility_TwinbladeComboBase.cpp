// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/GameplayAbility_TwinbladeComboBase.h"

#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Player/CharacterBase.h"


void UGameplayAbility_TwinbladeComboBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                          const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                          const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	CommitAbility(Handle,ActorInfo,ActivationInfo);

	mAbilitySpecHandle = Handle;
	mActorInfo = ActorInfo;
	mActivationInfo=ActivationInfo;

	// 첫번째 공격일 경우 다음 공격에 대한 이벤트를 수신할 필요없이 바로 공격을 실행합니다.
	if(IsFirstAttack)
	{
		ActiveMontage();
	}
	// 첫번째 공격외의 공격은 애님 노티파이의 NextAttack 이벤트를 수신하여 공격을 수행합니다.
	// 첫번째 공격 실행 후 바로 두번째 공격을 실행하지 않기 위해 애님노티파이를 통해 몽타주 실행중 특정 구간에서 다음 공격을 수행하도록
	// 이벤트를 수신하면 몽타주를 수행하도록 하였습니다.
	else
	{
		UAbilityTask_WaitGameplayEvent* WaitNextAttackGameplayEvent=UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this,FGameplayTag::RequestGameplayTag("Ability.State.NextAttack"),nullptr,true,true);
		WaitNextAttackGameplayEvent->EventReceived.AddDynamic(this,&UGameplayAbility_TwinbladeComboBase::NextAttackEventReceived);
		WaitNextAttackGameplayEvent->Activate();	
	}

	//모션워핑이 필요하다면 모션워프를 실행합니다.(애니메이션이 루트모션이 아닌 경우 MotionWarp를 통해 이동시켜줍니다.)
	if(DoMotionWarp)
	{
		MotionWarp();
	}

	WaitGameplayEventForApplyDamageEffect();
}

/**
 * 
 */
void UGameplayAbility_TwinbladeComboBase::NextAttackEventReceived(FGameplayEventData Payload)
{
	ActiveMontage();
}

void UGameplayAbility_TwinbladeComboBase::MotionWarp()
{
	ACharacterBase* Player = Cast<ACharacterBase>(GetOwningActorFromActorInfo());
	Player->AttackWithMotionWarp();
}
