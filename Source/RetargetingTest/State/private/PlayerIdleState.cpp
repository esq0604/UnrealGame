// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/State/Public/PlayerIdleState.h"

#include "RetargetingTest/Component/Public/BaseStateManagerComponent.h"

UPlayerIdleState::UPlayerIdleState()
{
	StateGameplayTag.FromExportString("State.Idle");
}

/**
 * Idle State의 진입 조건입니다.
 */
bool UPlayerIdleState::CanPerformState()
{
	if(PerformingActor->GetVelocity()==FVector::ZeroVector)
		return true;
	
	return false;
}
