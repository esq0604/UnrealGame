// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/UI/Public/Inventory.h"

#include "Blueprint/WidgetTree.h"
#include "RetargetingTest/UI/Public/Slot.h"

void UInventory::NativeConstruct()
{
	Super::NativeConstruct();

}

/**
 * 인벤토리의 초기화 부분입니다. 각 슬롯에 타입을 인벤토리 타입으로 지정해줍니다.
 */
void UInventory::Init()
{
	TArray<UWidget*> Widgets;
	WidgetTree->GetAllWidgets(Widgets);
	Slots.Init(nullptr,12);

	for(UWidget* widget : Widgets)
	{
		USlot* slot =nullptr;
		slot = Cast<USlot>(widget);
		if(slot != nullptr)
		{
			UE_LOG(LogTemp,Warning,TEXT("Inventory Init %s"),*slot->GetName());
			slot->SetType(ESlotType::SLOT_INVENTORY);
			slot->Init();
			Slots[slot->GetSlotNum()]=slot;
		}
	}
}

