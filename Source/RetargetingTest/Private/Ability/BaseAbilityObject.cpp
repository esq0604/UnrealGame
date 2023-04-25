// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/Ability/BaseAbilityObject.h"

#include "RetargetingTest/Public/Component/BaseAbilityManagerComponent.h"
#include "RetargetingTest/Public/Player/CharacterBase.h"

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
	AbilityManagerComponent->SetCurrentActiveAbility(this);
}

bool UBaseAbilityObject::CanPerformAbility()
{
	return true;
}

void UBaseAbilityObject::EndAbility()
{
	UE_LOG(LogTemp,Warning,TEXT("BaseAbility EndAbility"));

}


void UBaseAbilityObject::PlayAbilityMontage(UAnimMontage* MontageToPlay)
{
	ACharacterBase* LocalCharacter = dynamic_cast<ACharacterBase*>(PerformingActor);
	LocalCharacter->GetMesh()->GetAnimInstance()->Montage_Play(MontageToPlay);
	SetActiveAbilityMontage(MontageToPlay);
}
