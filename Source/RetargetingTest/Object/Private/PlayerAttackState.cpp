// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Object/Public/PlayerAttackState.h"

#include "RetargetingTest/Component/Public/BaseStateManagerComponent.h"

UPlayerAttackState::UPlayerAttackState()
{
	StateGameplayTag.FromExportString("State.Attack");
}

bool UPlayerAttackState::CanPerformState()
{
	//TODO: AttackState CanPerform State 지정해줘야함.
	return true;	
}
