// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Object/Public/PlayerBlockState.h"
#include "RetargetingTest/Player/Public/RetargetingTestCharacter.h"
UPlayerBlockState::UPlayerBlockState()
{
	StateGameplayTag=GameTags::Get().State_Block;
}

bool UPlayerBlockState::CanPerformState()
{
	return true;
}

void UPlayerBlockState::StartState()
{
	Super::StartState();
	ARetargetingTestCharacter* Character=Cast<ARetargetingTestCharacter>(PerformingActor);
	Character->SetbCanbeDamaged(false);
}

void UPlayerBlockState::EndState()
{
	Super::EndState();
	ARetargetingTestCharacter* Character=Cast<ARetargetingTestCharacter>(PerformingActor);
	Character->SetbCanbeDamaged(true);
}


