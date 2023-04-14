// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/State/Public/PlayerEquipState.h"
#include "RetargetingTest/Ability/public/BaseAbilityObject.h"
#include "RetargetingTest/Component/Public/BaseAbilityManagerComponent.h"

UPlayerEquipState::UPlayerEquipState()
{
	StateGameplayTag.FromExportString("State.Equip");
}

void UPlayerEquipState::StartState()
{
	Super::StartState();
	AbilityManagerComponent->PerformAbilityOfClass(SelectedAbilityToTrigger);
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
}

