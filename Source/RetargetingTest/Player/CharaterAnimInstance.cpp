// Fill out your copyright notice in the Description page of Project Settings.


#include "CharaterAnimInstance.h"
#include "RetargetingTestCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RetargetingTest/Component/AttackComponent.h"

UCharaterAnimInstance::UCharaterAnimInstance(const FObjectInitializer& ObjectInitializer)
{

}

void UCharaterAnimInstance::PlayAttackMontage()
{
	Montage_Play(AttackMontage,1.0f);
}

void UCharaterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	
	// character=Cast<ARetargetingTestCharacter>(GetOwningActor());
	// bIsTrunLeft=character->GetIsTurnLeft();
	// bIsTrunRight=character->GetIsTurnRight();
}

void UCharaterAnimInstance::AnimNotify_SaveAttack()
{
	
}

void UCharaterAnimInstance::AnimNotify_EnableCollision()
{
	OnAttackHitCheck.Broadcast();
	
}

void UCharaterAnimInstance::AnimNotify_DisableCollision()
{
}

