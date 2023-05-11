// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/Object/Potion.h"
#include "RetargetingTest/Public/Player/CharacterBase.h"


void APotion::UseItem(ACharacterBase* Character)
{
	Super::UseItem(Character);
	Use(Character);
}

/**
 * 아이템을 사용하고 개수를 차감합니다.
 */
void APotion::Use(ACharacterBase* Character)
{
	// const float CurrentCharacterHp=Character->GetStatComponent()->GetCurrentHp();
	// Character->GetStatComponent()->SetHP(CurrentCharacterHp+HpValue);
	// Count--;
}

