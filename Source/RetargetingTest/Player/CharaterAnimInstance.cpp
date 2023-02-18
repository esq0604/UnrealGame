// Fill out your copyright notice in the Description page of Project Settings.


#include "CharaterAnimInstance.h"
#include "RetargetingTestCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RetargetingTest/Component/AttackComponent.h"

UCharaterAnimInstance::UCharaterAnimInstance(const FObjectInitializer& ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT("/Game/ParagonAurora/Characters/Heroes/Aurora/Animations/Primary_Attack_A_Montage"));

	if(ATTACK_MONTAGE.Succeeded())
	{
		AttackMontage=ATTACK_MONTAGE.Object;
	}
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

