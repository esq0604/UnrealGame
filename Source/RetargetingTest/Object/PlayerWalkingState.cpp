// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWalkingState.h"

#include "GameFramework/PawnMovementComponent.h"
#include "RetargetingTest/Player/RetargetingTestCharacter.h"

bool UPlayerWalkingState::CanPerformState()
{
	ARetargetingTestCharacter* Character=Cast<ARetargetingTestCharacter>(PerformingActor);
	if(PerformingActor->GetVelocity().Length()>0 && Character->GetMovementComponent()->IsFalling())
		return true;

	return Super::CanPerformState();
}
