// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Ability/Public/PlayerEquipAbility.h"

#include "RetargetingTest/Component/Public/BaseStateManagerComponent.h"
#include "RetargetingTest/State/Public/BaseStateObject.h"

UPlayerEquipAbility::UPlayerEquipAbility()
{
}

void UPlayerEquipAbility::StartAbility()
{
	Super::StartAbility();
	UE_LOG(LogTemp,Warning,TEXT("UPlayerEquipAbility::StartAbility"));
	if(EquipMontage==nullptr)
	{
		TArray<UAnimMontage*> LocalMontageList=GetAbilityMontage(this->GetClass());
		const int32 LocalMontageSize = LocalMontageList.Num();
		const int32 RandomIdx=FMath::RandRange(0,LocalMontageSize-1);
		PlayAbilityMontage(LocalMontageList[RandomIdx]);
	}
	else
	{
		PlayAbilityMontage(EquipMontage);
	}
}

bool UPlayerEquipAbility::CanPerformAbility()
{
	if(StateManagerComponent->GetCurrentActiveState())
	{
		const FGameplayTag IdleStateTag = FGameplayTag::RequestGameplayTag("State.Idle");
		const FGameplayTag SprintStateTag = FGameplayTag::RequestGameplayTag("State.Sprint");
		const FGameplayTag WalkStateTag = FGameplayTag::RequestGameplayTag("State.Walk");
		const FGameplayTag CurrentStateTag =StateManagerComponent->GetCurrentActiveState()->GetGameplayTag();
		
		const bool CanPerform=CurrentStateTag==IdleStateTag || CurrentStateTag==SprintStateTag || CurrentStateTag == WalkStateTag;

		if(CanPerform && GetAbilityMontage(GetClass()).Num()>0)
		{
			return true;
		}
	}
	return false;
}
