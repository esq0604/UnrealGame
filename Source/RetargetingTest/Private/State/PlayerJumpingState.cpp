// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/State/PlayerJumpingState.h"

UPlayerJumpingState::UPlayerJumpingState()
{
	StateGameplayTag.FromExportString("State.Jump");
}

bool UPlayerJumpingState::CanPerformState()
{
	return Super::CanPerformState();
}
