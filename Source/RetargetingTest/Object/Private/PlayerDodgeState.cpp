// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Object/Public/PlayerDodgeState.h"

#include "RetargetingTest/Component/Public/BaseStateManagerComponent.h"

UPlayerDodgeState::UPlayerDodgeState()
{
	StateGameplayTag.FromExportString("State.Dodge");

}

bool UPlayerDodgeState::CanPerformState()
{
	if(StateManagerComponent->GetCurrentActiveState()->GetGameplayTag()==FGameplayTag::RequestGameplayTag("State.Walk"))
	{
		return true;
	}    
	return false;
}
