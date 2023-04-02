// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Object/Public/PlayerBlockState.h"
#include "RetargetingTest/Player/Public/RetargetingTestCharacter.h"
UPlayerBlockState::UPlayerBlockState()
{
	StateGameplayTag.FromExportString("State.Block");
}

bool UPlayerBlockState::CanPerformState()
{
	UE_LOG(LogTemp,Warning,TEXT("BlockState CanPerform State"));
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


