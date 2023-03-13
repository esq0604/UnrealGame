// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/UI/Public/Slot.h"

#include "Components/Image.h"
#include "RetargetingTest/Player/Public/RetargetingTestCharacter.h"


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
			UE_LOG(LogTemp,Warning,TEXT("Slot Index %d"),Index);
			UTexture2D* Tex=Character->GetThumnailAtInventorySlot(Index);
			if(Tex!=nullptr)
			{
				Img->SetBrushFromTexture(Tex);
			}
		}
		break;
	}
}

void USlot::SetType(ESlotType NewSlotType)
{
	SlotType=NewSlotType;
}

void USlot::SetCharacter(ARetargetingTestCharacter* NewCharacter)
{
	Character=NewCharacter;
}

int32 USlot::GetSlotNum() const
{
	return SlotNum;
}
