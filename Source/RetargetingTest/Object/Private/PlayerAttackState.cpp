// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Object/Public/PlayerAttackState.h"

#include "RetargetingTest/Component/Public/BaseStateManagerComponent.h"

UPlayerAttackState::UPlayerAttackState()
{
	StateGameplayTag.FromExportString("State.Attack");
}

bool UPlayerAttackState::CanPerformState()
{
	if(StateManagerComponent->GetCurrentActiveState()==nullptr)
		return false;
	if(StateManagerComponent->GetCurrentActiveState()->GetGameplayTag()==FGameplayTag::RequestGameplayTag("State.Walk"))
	{
		return true;
	}
	return false;
}
