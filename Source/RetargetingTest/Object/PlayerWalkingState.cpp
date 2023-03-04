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
	if(PerformingActor!= nullptr)
	{
		ARetargetingTestCharacter* PerformingCharacter=Cast<ARetargetingTestCharacter>(PerformingActor);
			if(PerformingCharacter->GetVelocity().Size()>0 && !PerformingCharacter->GetMovementComponent()->IsFalling())return true;
		
	}
	return false;
}

void UPlayerWalkingState::EndState()
{
	Super::EndState();
}

void UPlayerWalkingState::StartState()
{
	Super::StartState();
}


