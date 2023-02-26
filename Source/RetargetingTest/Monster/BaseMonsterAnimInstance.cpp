// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMonsterAnimInstance.h"

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

void UBaseMonsterAnimInstance::AnimNotify_DoDamage()
{
	OnDoDamage.Broadcast();
}
