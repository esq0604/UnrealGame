// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Object/Public/PlayerBlockState.h"
#include "RetargetingTest/Player/Public/CharacterBase.h"
UPlayerBlockState::UPlayerBlockState()
{
	StateGameplayTag.FromExportString("State.Block");
}

bool UPlayerBlockState::CanPerformState()
{
	return true;
}

void UPlayerBlockState::StartState()
{
	Super::StartState();
	ACharacterBase* Character=Cast<ACharacterBase>(PerformingActor);
	Character->SetbCanbeDamaged(false);
}

void UPlayerBlockState::EndState()
{
	Super::EndState();
	ACharacterBase* Character=Cast<ACharacterBase>(PerformingActor);
	Character->SetbCanbeDamaged(true);
}


