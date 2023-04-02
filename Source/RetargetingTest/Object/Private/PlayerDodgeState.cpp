// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Object/Public/PlayerDodgeState.h"

#include "RetargetingTest/Component/Public/BasePlayerStatComponent.h"
#include "RetargetingTest/Component/Public/BaseStateManagerComponent.h"
#include "RetargetingTest/Player/Public/RetargetingTestCharacter.h"

UPlayerDodgeState::UPlayerDodgeState()
{
	StateGameplayTag.FromExportString("State.Dodge");
}

void UPlayerDodgeState::StartState()
{
	Super::StartState();
	ARetargetingTestCharacter* Character=Cast<ARetargetingTestCharacter>(PerformingActor);
	Character->SetbCanbeDamaged(false);
	const float CharacterCurrentStamina=Character->GetStatComponent()->GetCurrentStamina();
	Character->GetStatComponent()->SetStamina(CharacterCurrentStamina-10.0f);
}

bool UPlayerDodgeState::CanPerformState()
{
	if(StateManagerComponent->GetCurrentActiveState()->GetGameplayTag()==FGameplayTag::RequestGameplayTag("State.Walk"))
	{
		return true;
	}    
	return false;
}

void UPlayerDodgeState::EndState()
{
	Super::EndState();
	ARetargetingTestCharacter* Character=Cast<ARetargetingTestCharacter>(PerformingActor);
	Character->SetbCanbeDamaged(true);
}
