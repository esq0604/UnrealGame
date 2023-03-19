// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Object/Public/Potion.h"

#include "RetargetingTest/Component/Public/BasePlayerStatComponent.h"
#include "RetargetingTest/Player/Public/RetargetingTestCharacter.h"

void APotion::UseItem(ARetargetingTestCharacter* Character)
{
	Super::UseItem(Character);
	Use(Character);
}

void APotion::Use(ARetargetingTestCharacter* Character)
{
	const float CurrentCharacterHp=Character->GetStatComponent()->GetCurrentHp();
	Character->GetStatComponent()->SetHP(CurrentCharacterHp+HpValue);
}

int APotion::GetCount() const
{
	return Count;
}
