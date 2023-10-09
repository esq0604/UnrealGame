// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/Object/Potion.h"

#include "Attribute/BaseAttributeSet.h"
#include "RetargetingTest/Public/Player/CharacterBase.h"


void APotion::UseItem_Implementation(ACharacterBase* Character)
{
	if(Count>0)
	{
		FGameplayAttributeData Health= Character->GetAttributes()->Health;
		Health.SetCurrentValue(RecoveryAmount);
		Count--;
	}

	return;
}

int32 APotion::GetCount_Implementation()
{
	return Count;
}


