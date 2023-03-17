// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Object/Public/SlotDragDrop.h"

#include "Kismet/GameplayStatics.h"
#include "RetargetingTest/Player/Public/RetargetingTestCharacter.h"
#include "RetargetingTest/UI/Public/Slot.h"
#include "RetargetingTest/Object/Public/PickUp.h"

/**
 * 슬롯을 드래그 후 드랍시 호출되는 함수입니다. 
 * @param to -변경될 위치의 슬롯이들어옵니다. 
 */
bool USlotDragDrop::Drop(USlot* To)
{
	switch(From->GetSlotType())
	{
	case ESlotType::SLOT_INVENTORY:
		{
			if(To->GetSlotType()==ESlotType::SLOT_INVENTORY)return SwapInven(To);
			if(To->GetSlotType()==ESlotType::SLOT_QUICK) return SetQuickSlot(To);
		}
	case ESlotType::SLOT_QUICK:
		{
			if(To->GetSlotType()==ESlotType::SLOT_QUICK) return SwapQuickSlot(To);

		}
	}
	return false;
}

/**
 * 인벤토리에서 스왑할시, 퀵슬롯에서도 스왑된 정보를 통해 아이템을 사용할 수 있도록 해야합니다.
 */
bool USlotDragDrop::SwapInven(USlot* to)
{
	//From에 있는 ReferenceSlot을 지우고 스왑 후 To의 referenceSlot에 추가합니다.
	Character->Inventory.Swap(From->GetSlotIndex(), to->GetSlotIndex());
	From->Refresh();
	to->Refresh();

	return true;
}

bool USlotDragDrop::SetQuickSlot(USlot* To)
{
	if(To!=nullptr && Character!=nullptr)
	{
		Character->Inventory[From->GetSlotIndex()]->AddReferenceSlot(To);
		To->SetType(ESlotType::SLOT_QUICK);
		To->Index=From->Index;
		To->Refresh();
	}
	return true;
}

bool USlotDragDrop::SwapQuickSlot(USlot* To)
{
	if(From->GetSlotType() == To->GetSlotType())
	{

		Character->Inventory[From->GetSlotIndex()]->RemoveReferenceSlot(From);
		Character->Inventory[From->GetSlotIndex()]->AddReferenceSlot(To);

		//2. 인덱스를 바꿉니다.(인덱스를 바꾸어 슬롯의 이미지를 변경함)
		const int TempIndex = To->Index;
		To->Index=From->Index;
		From->Index=TempIndex;

		if(TempIndex<0)
			From->SetImg(nullptr);
		
		To->Refresh();
		From->Refresh();
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Different Type From ,To"));
	}
	return true;
}

