// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSprintingState.h"

UPlayerSprintingState::UPlayerSprintingState()
{
	StateGameplayTag.FromExportString("State.Sprint");

}

bool UPlayerSprintingState::CanPerformState()
{
	return Super::CanPerformState();
}
