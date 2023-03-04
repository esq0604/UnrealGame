// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerJumpingState.h"

#include "GameFramework/PawnMovementComponent.h"
#include "RetargetingTest/Player/RetargetingTestCharacter.h"

UPlayerJumpingState::UPlayerJumpingState()
{
	StateGameplayTag.FromExportString("State.Jump");
}

bool UPlayerJumpingState::CanPerformState()
{
	return Super::CanPerformState();
}
