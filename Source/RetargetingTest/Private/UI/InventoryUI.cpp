// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/UI/InventoryUI.h"

#include "Blueprint/WidgetTree.h"
#include "Component/InventoryComponent.h"
#include "Components/UniformGridPanel.h"
#include "Data/ItemDataAsset.h"
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
	TArray<UWidget*> WeaponItemSlots = WeaponItemsPanel->GetAllChildren();
	TArray<UWidget*> ToolItemSlots = ToolItemsPanel->GetAllChildren();
	TArray<UWidget*> QuestItemSlots = QuestItemsPanel->GetAllChildren();
	TArray<UWidget*> MagicItemSlots = MagicItemsPanel->GetAllChildren();

	for(int i=0; i<MAX_SLOT_NUM; i++)
	{
		USlot* weaponSlot = Cast<USlot>(WeaponItemSlots[i]);
		USlot* toolSlot = Cast<USlot>(ToolItemSlots[i]);
		USlot* questSlot = Cast<USlot>(QuestItemSlots[i]);
		USlot* magicSlot = Cast<USlot>(MagicItemSlots[i]);

		if(weaponSlot!=nullptr)
		{
			weaponSlot->SetIndex(i);
			weaponSlot->SetInventoryComponent(InventoryComponent);
			weaponSlot->HideAmountText();
			WeaponSlots.Add(weaponSlot);
		}
		if(toolSlot!=nullptr)
		{
			toolSlot->SetIndex(i);
			toolSlot->SetInventoryComponent(InventoryComponent);
			toolSlot->HideAmountText();
			ToolSlots.Add(toolSlot);
		}
		if(questSlot!=nullptr)
		{
			questSlot->SetIndex(i);
			questSlot->SetInventoryComponent(InventoryComponent);
			questSlot->HideAmountText();
			QuestSlots.Add(questSlot);
		}
		if(magicSlot!=nullptr)
		{
			magicSlot->SetIndex(i);
			magicSlot->SetInventoryComponent(InventoryComponent);
			magicSlot->HideAmountText();
			MagicSlots.Add(magicSlot);
		}
	}
	
}

/**
 * @brief 아이템타입에 해당하는 슬롯의 인덱스에 대한 텍스처,수량텍스트 등 보여지는 요소를 지웁니다.
 * @param ItemType 들어올 아이템의 타입입니다.
 * @param Index 수정할 슬롯의 인덱스입니다.
 */
void UInventoryUI::RemoveItem(EItemType ItemType, int32 Index)
{
	UE_LOG(LogTemp,Warning,TEXT("Remove Item"));
	GetSlot(ItemType,Index)->SetImg(nullptr);
	GetSlot(ItemType,Index)->SetToolTipText(FText::GetEmpty());
}

void UInventoryUI::HideAmountText(EItemType ItemType, int32 Index)
{
	GetSlot(ItemType,Index)->HideAmountText();
}

void UInventoryUI::SetTexture(EItemType ItemType,int32 Index, UTexture2D* InTexture)
{
	GetSlot(ItemType,Index)->SetImg(InTexture);
}

void UInventoryUI::SetAmountText(EItemType ItemType, int32 Index, int32 Quantity)
{
	GetSlot(ItemType,Index)->SetAmountText(FText::FromString(FString::FromInt(Quantity)));
}

void UInventoryUI::SetInventoryComponent(UInventoryComponent* NewInventoryComponent)
{
	InventoryComponent = NewInventoryComponent;
}



USlot* UInventoryUI::GetSlot(EItemType Type,int32 Index) const
{
	switch (Type)
	{
	case EItemType::Weapon:
		return WeaponSlots[Index];
		break;
	case EItemType::Tool:
		return ToolSlots[Index];
		break;
	
		
		default: return nullptr;
	}
}

TArray<USlot*> UInventoryUI::GetSlots(EItemType Type) const
{
	switch (Type)
	{
	case EItemType::Weapon:
		return WeaponSlots;
		break;
	case EItemType::Tool:
		return ToolSlots;
		break;

		default:
			return TArray<USlot*>();
	}
}

int32 UInventoryUI::GetEmptySlotIndex(EItemType Type) const
{
	return GetSlots(Type).Find(nullptr);
}

