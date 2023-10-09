// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/UI/InventoryUI.h"

#include "Blueprint/WidgetTree.h"
#include "Component/InventoryComponent.h"
#include "RetargetingTest/Public/Player/CharacterBase.h"
#include "RetargetingTest/Public/UI/Slot.h"

void UInventoryUI::NativeConstruct()
{
	Super::NativeConstruct();

}

/**
 * 인벤토리의 초기화 부분입니다. 각 슬롯에 타입을 인벤토리 타입으로 지정해줍니다.
 */
void UInventoryUI::Init()
{
	if(Player)
	{
		UInventoryComponent* InventoryComp = Player->GetInventoryManagerComponent();
		TArray<UWidget*> Widgets;
		WidgetTree->GetAllWidgets(Widgets);
		Slots.Init(nullptr,InventoryComp->GetInventory().Num());
		
		for(UWidget* widget : Widgets)
		{
			USlot* slot =nullptr;
			slot = Cast<USlot>(widget);
			if(slot != nullptr)
			{
				slot->SetType(ESlotType::SLOT_INVENTORY);
				slot->SetInventoryComponent(InventoryComp);
				slot->Init();
				Slots[slot->GetIndex()]=slot;
			
			}
		}
	}
}

void UInventoryUI::RefreshAllSlot()
{
	for(USlot* slot : Slots)
	{
		slot->Refresh();
	}
}

void UInventoryUI::RefreshSlotByIndex(int32 Index)
{
	Slots[Index]->Refresh();
}

void UInventoryUI::SetCharacter(ACharacterBase* NewCharacter)
{
	Player= NewCharacter;
}

USlot* UInventoryUI::GetSlot(int32 Index) const
{
	return Slots[Index];
}

