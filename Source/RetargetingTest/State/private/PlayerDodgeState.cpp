// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/State/Public/PlayerDodgeState.h"

#include "RetargetingTest/Component/Public/BasePlayerStatComponent.h"
#include "RetargetingTest/Component/Public/BaseStateManagerComponent.h"
#include "RetargetingTest/Player/Public/CharacterBase.h"

UPlayerDodgeState::UPlayerDodgeState()
{
	StateGameplayTag.FromExportString("State.Dodge");
}

void UPlayerDodgeState::StartState()
{
	Super::StartState();
	ACharacterBase* Character=Cast<ACharacterBase>(PerformingActor);
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
	ACharacterBase* Character=Cast<ACharacterBase>(PerformingActor);
	Character->SetbCanbeDamaged(true);
}
