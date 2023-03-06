// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Monster/Public/BaseMonsterAnimInstance.h"

UBaseMonsterAnimInstance::UBaseMonsterAnimInstance()
	:mSpeed(0)
{
}

void UBaseMonsterAnimInstance::PlayHitMontage()
{
	Montage_Play(mHitMontage);
}

void UBaseMonsterAnimInstance::PlayDeadMontage()
{
	Montage_Play(mDeadMontage);
}

/**
 * 데미지 줄때(공격시)실행하는 애니메이션의 노티파이입니다. BaseMonster의 AttackCheck와 바인딩 되어있습니다.
 */
void UBaseMonsterAnimInstance::AnimNotify_DoDamage()
{
	OnAttackHitCheckDelegate.Broadcast();
}


