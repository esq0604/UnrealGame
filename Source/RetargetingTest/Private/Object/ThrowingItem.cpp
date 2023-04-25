// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/Object/ThrowingItem.h"

/**
 * 
 */
void AThrowingItem::UseItem(ACharacterBase* Character)
{
	Super::UseItem(Character);
}

/**
 * 사용했을시 아이템에서 발생해야하는 효과가 작성됩니다.
 * @param Character - 게임 플레이어 캐릭터가 들어옵니다.
 */
void AThrowingItem::Use(ACharacterBase* Character)
{
	if(Count>0)
	{
		Count--;
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Num of Item is 0"));
	}
}

