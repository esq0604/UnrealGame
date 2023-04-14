// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Ability/Public/PlayerEquipAbility.h"

UPlayerEquipAbility::UPlayerEquipAbility()
{
}

void UPlayerEquipAbility::StartAbility()
{
	Super::StartAbility();
	UE_LOG(LogTemp,Warning,TEXT("UPlayerEquipAbility::StartAbility"));
	if(EquipMontage==nullptr)
	{
		TArray<UAnimMontage*> LocalMontage=GetAbilityMontage(this->GetClass());
		const int32 LocalMontageSize = LocalMontage.Num();
		const int32 RandomIdx=FMath::RandRange(0,LocalMontageSize-1);
		PlayAbilityMontage(LocalMontage[RandomIdx]);
	}
	else
	{
		PlayAbilityMontage(EquipMontage);
	}
}
