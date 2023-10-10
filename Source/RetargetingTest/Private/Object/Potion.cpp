// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/Object/Potion.h"

#include "Attribute/BaseAttributeSet.h"
#include "Player/PlayerStateBase.h"
#include "RetargetingTest/Public/Player/CharacterBase.h"


void APotion::UseItem_Implementation(ACharacterBase* Character)
{

	UBaseAttributeSet* Attributes = Character->GetAttributes();
		if(Count>0)
		{
			if(Attributes!=nullptr)
			{
				FGameplayAttributeData Health= Attributes->Health;
				Health.SetCurrentValue(Health.GetCurrentValue()+RecoveryAmount);
				Count--;
			}
		}
	
	return;
}

int32 APotion::GetCount_Implementation()
{
	return Count;
}


