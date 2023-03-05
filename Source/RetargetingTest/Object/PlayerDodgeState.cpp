// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerDodgeState.h"

#include "RetargetingTest/Component/BaseStateManagerComponent.h"

UPlayerDodgeState::UPlayerDodgeState()
{
	StateGameplayTag.FromExportString("State.Dodge");
}

bool UPlayerDodgeState::CanPerformState()
{
	//닷지 스테이트가 활성화 되기 위해서는, WalkState 상태 이여야합니다.
	
	if(StateManagerComponent->GetCurrentActiveState()==StateManagerComponent->ActiveAbleStates[4])
	{
		return true;
	}
	return false;
}
