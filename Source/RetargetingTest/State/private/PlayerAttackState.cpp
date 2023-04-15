// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/State/Public/PlayerAttackState.h"

#include "RetargetingTest/Component/Public/BaseAbilityManagerComponent.h"
#include "RetargetingTest/Component/Public/BaseStateManagerComponent.h"

UPlayerAttackState::UPlayerAttackState()
{
	StateGameplayTag.FromExportString("State.Attack");
}

bool UPlayerAttackState::CanPerformState()
{
	UE_LOG(LogTemp,Warning,TEXT("AttackState CanPerform State"));

	return CheckAbilitesToRun(AttackAbilites);
}

void UPlayerAttackState::StartState()
{
	Super::StartState();

	for(TSubclassOf<UBaseAbilityObject> AttackAbility : AttackAbilites)
	{
		UE_LOG(LogTemp,Warning,TEXT("AttackState Start State"));
		SetSelectedAbility(AttackAbility);
		AbilityManagerComponent->PerformAbilityOfClass(GetSeletedAbility());
	}
}
