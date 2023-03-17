// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Object/Public/PlayerSprintingState.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "RetargetingTest/Component/Public/BasePlayerStatComponent.h"
#include "RetargetingTest/Component/Public/BaseStateManagerComponent.h"
#include "RetargetingTest/Player/Public/RetargetingTestCharacter.h"

UPlayerSprintingState::UPlayerSprintingState()
{
	StateGameplayTag.FromExportString("State.Sprint");
}

bool UPlayerSprintingState::CanPerformState()
{
	if(StateManagerComponent->GetCurrentActiveState()==nullptr)
		return false;
	if(StateManagerComponent->GetCurrentActiveState()->GetGameplayTag()==FGameplayTag::RequestGameplayTag("State.Walk"))
	{
		return true;
	}
	return false;
}
/**
 * SprintState로 변경하고 shift 입력을 땔때까지. 다른 상태로 변경되지 않도록 합니다.
 */
void UPlayerSprintingState::StartState()
{
	Super::StartState();
	HasTickState=true;
	GetStateManagerComponent()->SetCanChangeState(false);
	ARetargetingTestCharacter* Character=Cast<ARetargetingTestCharacter>(PerformingActor);
	Character->GetCharacterMovement()->MaxWalkSpeed=800.0f;
}
/**
 * SprintState가 끝난다면 Tick State를 멈추게됩니다.
 */
void UPlayerSprintingState::EndState()
{
	Super::EndState();
	
	ARetargetingTestCharacter* Character=Cast<ARetargetingTestCharacter>(PerformingActor);
	GetStateManagerComponent()->SetCanChangeState(true);
	HasTickState=false;
}
/**
 * Sprint 상태에 들어서면 Stamina를 소비하게 됩니다. 
 */
void UPlayerSprintingState::TickState()
{
	Super::TickState();
	ARetargetingTestCharacter* Character=Cast<ARetargetingTestCharacter>(PerformingActor);
	const float CharacterCurrentStamina=Character->GetStatComponent()->GetCurrentStamina();
	Character->GetStatComponent()->SetStamina(CharacterCurrentStamina-0.1f);
}
