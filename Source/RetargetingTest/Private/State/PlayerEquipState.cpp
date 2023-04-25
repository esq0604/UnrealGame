// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/State/PlayerEquipState.h"
#include "RetargetingTest/Public/Component/BaseAbilityManagerComponent.h"
#include "RetargetingTest/Public/Component/BaseStateManagerComponent.h"

UPlayerEquipState::UPlayerEquipState()
{
	StateGameplayTag.FromExportString("State.Equip");
}

void UPlayerEquipState::StartState()
{
	Super::StartState();
	IsEquipWeapon=true;
	AbilityManagerComponent->PerformAbilityOfClass(GetSeletedAbility());
}

bool UPlayerEquipState::CanPerformState()
{
	Super::CanPerformState();
	
	TArray<TSubclassOf<UBaseAbilityObject>> AbilitesToRun;
	AbilitesToRun.AddUnique(EquipAbility);
	return CheckAbilitesToRun(AbilitesToRun);
}

void UPlayerEquipState::EndState()
{
	Super::EndState();
	FGameplayTag IdleStateTag = FGameplayTag::RequestGameplayTag("State.Idle");
	UBaseStateObject* IdleState = StateManagerComponent->GetStateOfGameplayTag(IdleStateTag);
	StateManagerComponent->TryPerformStateOfClass(IdleState->GetClass(),true);
}

