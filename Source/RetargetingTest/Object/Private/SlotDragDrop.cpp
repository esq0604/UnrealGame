// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Object/Public/SlotDragDrop.h"

#include "RetargetingTest/Player/Public/CharacterBase.h"
#include "RetargetingTest/UI/Public/Slot.h"
#include "RetargetingTest/Object/Public/ItemBase.h"

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
 * 인벤토리에서 스왑할시, 레퍼런스 슬롯을 변경하여 인벤토리에서 사용한 아이템이 퀵슬롯에서도 반영되도록해야합니다.
 */
bool USlotDragDrop::SwapInven(USlot* to)
{
	//From에 있는 ReferenceSlot을 지우고 스왑 후 To의 referenceSlot에 추가합니다.
	//Reference 슬롯의 인덱스를 변경함으로써 퀵슬롯에서 사용할 인벤토리의 참조를 변경합니다.
	if(!Character->Inventory[From->GetIndex()]->ReferenceSlot.IsEmpty())
	{
		USlot* TempSlot =Character->Inventory[From->GetIndex()]->ReferenceSlot.Top();
		Character->Inventory[From->GetIndex()]->ReferenceSlot.Pop();
		Character->Inventory.Swap(From->GetIndex(), to->GetIndex());
		Character->Inventory[to->GetIndex()]->ReferenceSlot.Push(TempSlot);
		Character->Inventory[to->GetIndex()]->ReferenceSlot.Top()->SetIndex(to->GetIndex());
	}
	else
	{
		Character->Inventory.Swap(From->GetIndex(), to->GetIndex());
	}
	
	From->Refresh();
	to->Refresh();

	return true;
}

/**
 * 퀵슬롯을 등록하는 함수입니다. 플레이어의 인벤토리(아이템)의 참조 슬롯에 등록하고 초기 인덱스를 참조하는 인벤토리의 인덱스로 변경합니다.
 * @param To - 등록하게 될 슬롯이 들어옵니다.
 */
bool USlotDragDrop::SetQuickSlot(USlot* To)
{
	if(To!=nullptr && Character!=nullptr)
	{
		Character->Inventory[From->GetIndex()]->AddReferenceSlot(To);
		To->SetType(ESlotType::SLOT_QUICK);
		To->Index=From->Index;
		To->Refresh();
	}
	return true;
}

/**
 * 퀵슬롯이 서로 변경될때 호출되는 함수입니다.
 * 등록되지 않은 옮기고, 이미 등록된 퀵슬롯이라면 아이템의 참조 슬롯을 변경하고 인덱스를 바꿉니다.
 * @param To - 변경될 위치의 슬롯이 들어옵니다.
 */
bool USlotDragDrop::SwapQuickSlot(USlot* To)
{
	if(From->GetSlotType() == To->GetSlotType())
	{
		//-1 == 비어있다면 Swap이 아닌 Move입니다.
		if(To->GetIndex() == -1)
		{
			MoveQuickSlot(To);
		}
		else
		{
			if(Character->Inventory[To->Index]!=nullptr)
			{
				Character->Inventory[To->Index]->RemoveReferenceSlot(To);
				Character->Inventory[To->Index]->AddReferenceSlot(From);
			}
			Character->Inventory[From->GetIndex()]->RemoveReferenceSlot(From);
			Character->Inventory[From->GetIndex()]->AddReferenceSlot(To);

			//2. 인덱스를 바꿉니다.(인덱스를 바꾸어 슬롯의 이미지를 변경함)
			const int TempIndex = To->Index;
			To->Index=From->Index;
			From->Index=TempIndex;

			if(TempIndex<0)
				From->SetImg(nullptr);
		
			To->Refresh();
			From->Refresh();
		}

	}

	return true;
}

/**
 * SwapQuickSlot에서 To Slot이 아직 퀵슬롯으로 등록되지 않았을때 호출됩니다.
 * @param To - 변경될 위치의 슬롯이 들어옵니다.
 */
bool USlotDragDrop::MoveQuickSlot(USlot* To)
{
	int32 tempIdx = To->GetIndex();
	To->SetIndex(From->GetIndex());
	From->SetIndex(tempIdx);
	
	Character->Inventory[To->GetIndex()]->AddReferenceSlot(To);
	
	To->Refresh();
	From->Refresh();
	return true;
}

