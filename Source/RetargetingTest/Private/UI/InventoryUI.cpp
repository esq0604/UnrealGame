// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/UI/InventoryUI.h"

#include "Blueprint/WidgetTree.h"
#include "Component/InventoryComponent.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
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
			weaponSlot->SetItemType(EItemType::Weapon);
			weaponSlot->SetSlotType(ESlotType::SLOT_INVENTORY);
			weaponSlot->SetInventoryUI(this);
			weaponSlot->SetVisibility(ESlateVisibility::Collapsed);
			WeaponSlots.Add(weaponSlot);
		}
		if(toolSlot!=nullptr)
		{
			toolSlot->SetIndex(i);
			toolSlot->SetItemType(EItemType::Tool);
			toolSlot->SetSlotType(ESlotType::SLOT_INVENTORY);
			toolSlot->SetInventoryUI(this);
			toolSlot->SetVisibility(ESlateVisibility::Collapsed);
			ToolSlots.Add(toolSlot);
		}
		if(questSlot!=nullptr)
		{
			questSlot->SetIndex(i);
			questSlot->SetItemType(EItemType::Quest);
			questSlot->SetSlotType(ESlotType::SLOT_INVENTORY);
			questSlot->SetInventoryUI(this);
			questSlot->SetVisibility(ESlateVisibility::Collapsed);
			QuestSlots.Add(questSlot);
		}
		if(magicSlot!=nullptr)
		{
			magicSlot->SetIndex(i);
			magicSlot->SetItemType(EItemType::Magic);
			magicSlot->SetSlotType(ESlotType::SLOT_INVENTORY);
			magicSlot->SetInventoryUI(this);
			magicSlot->SetVisibility(ESlateVisibility::Collapsed);
			MagicSlots.Add(magicSlot);
		}
	}

	ItemDescriptionPanel->SetVisibility(ESlateVisibility::Collapsed);
}

/**
 * @brief 아이템타입에 해당하는 슬롯의 인덱스에 대한 텍스처,수량텍스트 등 보여지는 요소를 지웁니다.
 * @param ItemType 들어올 아이템의 타입입니다.
 * @param Index 수정할 슬롯의 인덱스입니다.
 */
void UInventoryUI::RemoveItem(EItemType ItemType, int32 Index)
{
	GetSlot(ItemType,Index)->SetImg(nullptr);
	GetSlot(ItemType,Index)->SetToolTipText(FText::GetEmpty());
	GetSlot(ItemType,Index)->SetVisibility(ESlateVisibility::Collapsed);
}

void UInventoryUI::SetTexture(EItemType ItemType,int32 Index, UTexture2D* InTexture)
{
	GetSlot(ItemType,Index)->SetImg(InTexture);
	GetSlot(ItemType,Index)->SetVisibility(ESlateVisibility::Visible);
}

void UInventoryUI::SetAmountText(EItemType ItemType, int32 Index, int32 Quantity)
{
	GetSlot(ItemType,Index)->SetAmountText(Quantity);
}

void UInventoryUI::HideAmountText(EItemType ItemType, int32 Index)
{
	GetSlot(ItemType,Index)->SetAmountText(1);
}

void UInventoryUI::SetInventoryComponent(UInventoryComponent* NewInventoryComponent)
{
	InventoryComponent = NewInventoryComponent;
}

/**
 * @brief 아이템 정의 패널을 보여줍니다.
 * @param Type 보여줄 아이템이 담긴 슬롯의 타입입니다.
 * @param Index 보여줄 아이템이 담긴 슬롯의 인덱스입니다.
 */
void UInventoryUI::ShowItemDescriptionPanel(EItemType Type, int32 Index)
{
	UItemDataAsset* Item=InventoryComponent->GetItem(Type,Index);
	ItemImage->SetBrushFromTexture(Item->AssetData.Icon);
	ItemName->SetText(Item->TextData.Name);
	ItemDescription->SetText(Item->TextData.Description);
	QuantityText->SetText(FText::Format(NSLOCTEXT("InterationWidget", "QuantityText", "{0} / {1}"),Item->NumericData.Quantity,Item->NumericData.MaxStackSize));
	ItemDescriptionPanel->SetVisibility(ESlateVisibility::Visible);
}

void UInventoryUI::HideItemDescriptionPanel()
{
	
	ItemDescriptionPanel->SetVisibility(ESlateVisibility::Collapsed);
}

void UInventoryUI::TryUseItem(EItemType Type, int32 Index)
{
	InventoryComponent->UseItem(Type,Index);
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

