// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Object/Public/PlayerAttackState.h"

#include "RetargetingTest/Component/Public/BaseStateManagerComponent.h"

UPlayerAttackState::UPlayerAttackState()
{
	StateGameplayTag.FromExportString("State.Attack");
}

bool UPlayerAttackState::CanPerformState()
{
	// if(StateManagerComponent->GetCurrentActiveState()->GetGameplayTag()==GameTags::Get().State_Walk)
	// {
	// 	return true;
	// }
	return false;
}
