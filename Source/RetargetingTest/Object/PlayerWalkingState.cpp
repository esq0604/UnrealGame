// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWalkingState.h"

#include "Chaos/Island/IslandGraph.h"
#include "GameFramework/PawnMovementComponent.h"
#include "RetargetingTest/Component/BaseStateManagerComponent.h"
#include "RetargetingTest/Player/RetargetingTestCharacter.h"

UPlayerWalkingState::UPlayerWalkingState()
{
	StateGameplayTag.FromExportString("State.Walk");
}

bool UPlayerWalkingState::CanPerformState()
{
	UE_LOG(LogTemp,Warning,TEXT("Walking State CanPerformState"));
	ARetargetingTestCharacter* Character=Cast<ARetargetingTestCharacter>(PerformingActor);
	if(PerformingActor->GetVelocity().Length()>0 && !Character->GetMovementComponent()->IsFalling())
		return true;

	return Super::CanPerformState();
}


