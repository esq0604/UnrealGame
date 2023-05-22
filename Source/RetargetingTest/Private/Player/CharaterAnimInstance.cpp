// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/Player/CharaterAnimInstance.h"
#include "GameplayTagContainer.h"
#include "RetargetingTest/Public/Player/CharacterBase.h"

UCharaterAnimInstance::UCharaterAnimInstance(const FObjectInitializer& ObjectInitializer)
{
}

void UCharaterAnimInstance::PlayAttackMontage()
{
	Montage_Play(AttackMontage,1.0f);
}


/**
 * CharacterAnimInstance를 사용하고 있는 캐릭터에 대해서 받아옵니다.
 */
void UCharaterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	OwnerCharacter=Cast<ACharacterBase>(GetOwningActor());
	//Montage_SetEndDelegate(OnMontageEnded);
}

bool UCharaterAnimInstance::GetIsBlocking() const
{
	return IsBlocking;
}

void UCharaterAnimInstance::SetIsBlocking(bool newIsBlocking)
{
	UE_LOG(LogTemp,Warning,TEXT("%d"),newIsBlocking);
	IsBlocking=newIsBlocking;
}





