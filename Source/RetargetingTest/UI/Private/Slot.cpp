// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/UI/Public/Slot.h"


void USlot::NativeConstruct()
{
	Super::NativeConstruct();
}

/**
 * 슬롯의 초기화 입니다. 슬롯에 부여된 번호를 인덱스로 지정합니다.
 */
void USlot::Init()
{
	switch (SlotType)
	{
	case ESlotType::SLOT_INVENTORY:
	case ESlotType::SLOT_QUICK:
		Index=SlotNum;
		break;
	}
}

void USlot::Refresh()
{
	switch(SlotType)
	{
	case ESlotType::SLOT_INVENTORY:
	case ESlotType::SLOT_QUICK:
		{
			//아이템이 소비될때 해야할 로직을 작성합니다.
		}
		break;
	}
}

void USlot::SetType(ESlotType NewSlotType)
{
	SlotType=NewSlotType;
}

int32 USlot::GetSlotNum() const
{
	return SlotNum;
}
