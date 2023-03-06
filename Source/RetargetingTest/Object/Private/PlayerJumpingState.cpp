// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Object/Public/PlayerJumpingState.h"

#include "GameFramework/PawnMovementComponent.h"
#include "RetargetingTest/Player/Public/RetargetingTestCharacter.h"

UPlayerJumpingState::UPlayerJumpingState()
{
	StateGameplayTag.FromExportString("State.Jump");
}

bool UPlayerJumpingState::CanPerformState()
{
	return Super::CanPerformState();
}
