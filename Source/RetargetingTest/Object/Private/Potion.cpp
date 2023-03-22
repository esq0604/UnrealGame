// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Object/Public/Potion.h"

#include "RetargetingTest/Component/Public/BasePlayerStatComponent.h"
#include "RetargetingTest/Player/Public/RetargetingTestCharacter.h"

void APotion::UseItem(ARetargetingTestCharacter* Character)
{
	Super::UseItem(Character);
	Use(Character);
}

/**
 * 아이템을 사용하고 개수를 차감합니다.
 */
void APotion::Use(ARetargetingTestCharacter* Character)
{
	const float CurrentCharacterHp=Character->GetStatComponent()->GetCurrentHp();
	Character->GetStatComponent()->SetHP(CurrentCharacterHp+HpValue);
	Count--;
}

