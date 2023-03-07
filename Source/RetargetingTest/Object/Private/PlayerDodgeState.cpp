// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Object/Public/PlayerDodgeState.h"

#include "RetargetingTest/Component/Public/BaseStateManagerComponent.h"

UPlayerDodgeState::UPlayerDodgeState()
{
	StateGameplayTag.FromExportString("State.Dodge");
	UE_LOG(LogTemp,Warning,TEXT("Dodge Constructor %s"),*StateGameplayTag.ToString());

}

bool UPlayerDodgeState::CanPerformState()
{
	if(StateManagerComponent->GetCurrentActiveState()->GetGameplayTag()==GameTags::Get().State_Walk)
	{
		return true;
	}    
	return false;
}
