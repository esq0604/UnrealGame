// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Ability/public/BaseAbilityObject.h"

#include "RetargetingTest/Player/Public/CharacterBase.h"

UBaseAbilityObject::UBaseAbilityObject()
{
	
}

void UBaseAbilityObject::SetActiveAbilityMontage(UAnimMontage* NewActiveMontage)
{
	ActiveAbilityMontage = NewActiveMontage;
}

void UBaseAbilityObject::SetPerformingActor(AActor* NewPerformingActor)
{
	PerformingActor = NewPerformingActor;
}

void UBaseAbilityObject::StartAbility()
{
}

bool UBaseAbilityObject::CanPerformAbility()
{
	return true;
}

void UBaseAbilityObject::PlayAbilityMontage(UAnimMontage* MontageToPlay)
{
	ACharacterBase* LocalCharacter = dynamic_cast<ACharacterBase*>(PerformingActor);
	LocalCharacter->GetMesh()->GetAnimInstance()->Montage_Play(MontageToPlay);
	SetActiveAbilityMontage(MontageToPlay);
}
