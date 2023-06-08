// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/Monster/BaseMonsterAnimInstance.h"

UBaseMonsterAnimInstance::UBaseMonsterAnimInstance()
	:mSpeed(0)
{
}


void UBaseMonsterAnimInstance::PlayDeadMontage()
{
	Montage_Play(mDeadMontage);
}


