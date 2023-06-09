// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/Monster/BaseMonsterAnimInstance.h"

UBaseMonsterAnimInstance::UBaseMonsterAnimInstance()
	:mSpeed(0)
{
}


void UBaseMonsterAnimInstance::PlayDeadMontage()
{
	Montage_Play(mDeadMontage);
	FOnMontageEnded CompleteDelegate;
	CompleteDelegate.BindUObject(this,&UBaseMonsterAnimInstance::DeadMontageEnded);

	FOnMontageBlendingOutStarted BlendingOutStarted;
	BlendingOutStarted.BindUObject(this,&UBaseMonsterAnimInstance::DeadMontageEnded);
}

void UBaseMonsterAnimInstance::DeadMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	UE_LOG(LogTemp,Warning,TEXT("Monster Dead"));
}



