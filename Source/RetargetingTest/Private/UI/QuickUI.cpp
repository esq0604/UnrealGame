// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/UI/QuickSlotUI.h"

#include "Blueprint/WidgetTree.h"
#include "RetargetingTest/Public/UI/Slot.h"
#include "UI/EquipmentSlot.h"

void UQuickSlotUI::Init()
{
	Slots.Init(nullptr,MAX_QUICK_SLOT);
	TArray<UWidget*> widgets;
	WidgetTree->GetAllWidgets(widgets);
	
	//RightHandSlot->SetEquipItemType(EEquipment_Type::Weapon);
	RightHandSlot->SlotNum=EQUIP_QUICK_SLOT;
	//LeftHandSlot->SetEquipItemType(EEquipment_Type::Weapon);
	LeftHandSlot->SlotNum=EQUIP_QUICK_SLOT;
	MainItemSlot->SlotNum=MAIN_ITEM_SLOT;
	SubItemSlot->SlotNum=SUB_ITEM_SLOT;
	MainMagicSlot->SlotNum=MAIN_MAGIC_SLOT;
	
	for(UWidget* widget : widgets)
	{
		USlot* slot = Cast<USlot>(widget);

		if(slot)
		{
			slot->SetType(ESlotType::SLOT_QUICK);
			slot->Init();
		}
	}

	SubItemSlot->SetVisibility(ESlateVisibility::Collapsed);
}

/**
 *  번호에 해당하는 퀵슬롯을 사용하도록 합니다.
 */
void UQuickSlotUI::Use()
{
	if(Slots[CurrentActionSlot]!=nullptr)
	Slots[CurrentActionSlot]->Action();
}

void UQuickSlotUI::SlotInit(USlot* InitSlot)
{
	
}

void UQuickSlotUI::SetInventoryComponent(UInventoryComponent* NewInventoryComponent)
{
	InventoryComponent=NewInventoryComponent;	
}

