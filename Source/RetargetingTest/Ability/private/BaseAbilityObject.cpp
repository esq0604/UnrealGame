// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Ability/public/BaseAbilityObject.h"

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