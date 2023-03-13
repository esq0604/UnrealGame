// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Object/Public/SlotDragDrop.h"

#include "RetargetingTest/Player/Public/RetargetingTestCharacter.h"
#include "RetargetingTest/UI/Public/Slot.h"
#include "RetargetingTest/Object/Public/PickUp.h"

/**
 * 슬롯을 드래그 후 드랍시 호출되는 함수입니다. 
 * @param to -변경될 위치의 슬롯이들어옵니다. 
 */
bool USlotDragDrop::Drop(USlot* to)
{
	switch(From->GetSlotType())
	{
	case ESlotType::SLOT_INVENTORY:
		{
			return SwapInven(to);
		}
	}
	return false;
}

bool USlotDragDrop::SwapInven(USlot* to)
{
	UE_LOG(LogTemp,Warning,TEXT("Before From Idex %d"),From->GetSlotIndex());
	UE_LOG(LogTemp,Warning,TEXT("Before To Idex %d"),to->GetSlotIndex());
	// UE_LOG(LogTemp,Warning,TEXT("SwapInven"));
	Character->Inventory.Swap(From->GetSlotIndex(), to->GetSlotIndex());
	// TArray<APickUp*> Inventory=Character->GetInventory();
	// Inventory[From->GetSlotIndex()]->SwapReferenceSlot(Inventory[to->GetSlotIndex()],From->GetSlotIndex(),to->GetSlotIndex());	
	UE_LOG(LogTemp,Warning,TEXT("After From Idex %d"),From->GetSlotIndex());
	UE_LOG(LogTemp,Warning,TEXT("After To Idex %d"),to->GetSlotIndex());

	From->Refresh();
	to->Refresh();

	return true;
}
