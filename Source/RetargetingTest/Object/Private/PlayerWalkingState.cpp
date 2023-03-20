// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Object/Public/PlayerWalkingState.h"

#include "Chaos/Island/IslandGraph.h"
#include "GameFramework/PawnMovementComponent.h"
#include "RetargetingTest/Component/Public/BaseStateManagerComponent.h"
#include "RetargetingTest/Player/Public/RetargetingTestCharacter.h"

UPlayerWalkingState::UPlayerWalkingState()
{
	StateGameplayTag=GameTags::Get().State_Walk;
	StateGameplayTag.FromExportString("State.Walk");
}

bool UPlayerWalkingState::CanPerformState()
{
	if(PerformingActor!= nullptr)
	{
		ARetargetingTestCharacter* PerformingCharacter=Cast<ARetargetingTestCharacter>(PerformingActor);
		if(PerformingCharacter->GetVelocity().Size()>150 && !PerformingCharacter->GetMovementComponent()->IsFalling())
			return true;
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



