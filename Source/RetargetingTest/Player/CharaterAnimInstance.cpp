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
	UE_LOG(LogTemp,Warning,TEXT("Do Play Attack Montage"));
	Montage_Play(AttackMontage,1.0f);
}



void UCharaterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	
	// character=Cast<ARetargetingTestCharacter>(GetOwningActor());
	// bIsTrunLeft=character->GetIsTurnLeft();
	// bIsTrunRight=character->GetIsTurnRight();
	//Montage_SetEndDelegate(OnMontageEnded);
}

void UCharaterAnimInstance::AnimNotify_SaveAttack()
{
	
}

void UCharaterAnimInstance::AnimNotify_AttackHitCheck()
{
	//UE_LOG(LogTemp,Warning,TEXT)
	OnAttackHitCheck.Broadcast();
}

void UCharaterAnimInstance::AnimNotify_NextAttackCheck()
{
	OnNextAttackHitCheck.Broadcast();
}

void UCharaterAnimInstance::JumpToAttackMontageSection(int32 NewSection)
{
	Montage_JumpToSection(GetAttackMontageSectionName(NewSection),AttackMontage);
}

FName UCharaterAnimInstance::GetAttackMontageSectionName(int32 Section)
{
	return FName(*FString::Printf(TEXT("Attack%d"),Section));
}




