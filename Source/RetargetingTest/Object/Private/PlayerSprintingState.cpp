// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Object/Public/PlayerSprintingState.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "RetargetingTest/Component/Public/BaseStateManagerComponent.h"
#include "RetargetingTest/Player/Public/RetargetingTestCharacter.h"

UPlayerSprintingState::UPlayerSprintingState()
{
	StateGameplayTag.FromExportString("State.Sprint");

}

bool UPlayerSprintingState::CanPerformState()
{
	if(StateManagerComponent->GetCurrentActiveState()==StateManagerComponent->ActiveAbleStates[4])
	{
		return true;
	}
	return false;
}

void UPlayerSprintingState::StartState()
{
	Super::StartState();     

	ARetargetingTestCharacter* Character=Cast<ARetargetingTestCharacter>(PerformingActor);
	Character->GetCharacterMovement()->MaxWalkSpeed=800.0f;
}

void UPlayerSprintingState::EndState()
{
	Super::EndState();
	
	ARetargetingTestCharacter* Character=Cast<ARetargetingTestCharacter>(PerformingActor);
	Character->GetCharacterMovement()->MaxWalkSpeed=500.0f;
}
