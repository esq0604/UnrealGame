// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/InventoryComponent.h"

#include "Controller/MyPlayerController.h"
#include "Data/ItemDataAsset.h"
#include "Interface/Useable.h"
#include "Player/CharacterBase.h"
#include "UI/InventoryUI.h"
#include "UI/PlayerHUD.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	// ...

	//melee weapon, tool, pants,chest, shoes, quest
	Items.Init(nullptr,16*6);
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
	ComponentOwner=Cast<ACharacterBase>(GetOwner());
	const AMyPlayerController* PC = Cast<AMyPlayerController>(ComponentOwner->GetController());
	const UPlayerHUD* PlayerHUD = PC->GetPlayerHUD();
	UQuickSlotUI* QuickSlot = PlayerHUD->GetQuickSlot();
	
	if(ensure(PC))
	{
		InventoryUI = PC->GetInventoryUI();
		EquipmentUI = PC->GetEquipmentUI();
	}
	
	for(UItemDataAsset* Item : StartingItems)
	{
		const int AvailAbleIndex= Items.Find(nullptr);
		Items[AvailAbleIndex] =  Item;
		
		if(Item->ItemType==EItemType::Armor && Item->ItemType==EItemType::Weapon)
		{
			//아이템을 스폰하여 플레이어에게 장착시키도록합니다.
		}

		//인벤토리 UI를 갱신합니다.
		UpdateSlot(AvailAbleIndex);
	}
}

/**
 * @brief 슬롯의 Index를 입력받아 InventoryUI를 업데이트합니다.
 * @param Index Update할 슬롯의 Index입니다.
 */
void UInventoryComponent::UpdateSlot(int32 Index)
{
	const UItemDataAsset* Item = Items[Index];

	if(Item!=nullptr)
	{
		
		InventoryUI->SetTexture(Item->ItemType,IndexNormalize(Index),Item->AssetData.Icon);
		if(Item->NumericData.Quantity==0)
		{
			Items[Index]=nullptr;
			InventoryUI->RemoveItem(Item->ItemType,IndexNormalize(Index));
		}
		else
		{
			if(Item->NumericData.IsStackable)
			{
				InventoryUI->SetAmountText(Item->ItemType,IndexNormalize(Index),Item->NumericData.Quantity);
			}
			else
			{
				InventoryUI->HideAmountText(Item->ItemType,IndexNormalize(Index));		
			}
		}
	}
	else
	{
		InventoryUI->RemoveItem(Item->ItemType,IndexNormalize(Index));
	}
}

bool UInventoryComponent::AddItem(UItemDataAsset* AddedItem)
{
	if(AddedItem!=nullptr)
	{
		const int32 AvailableIndex=Items.Find(nullptr);
		Items[AvailableIndex]=AddedItem;
		UpdateSlot(AvailableIndex);
		
	}
	return false;
}

/**
 *  인벤토리에있는 아이템을사용합니다. 장비아이템의 경우 장착을하고, 소비아이템인경우 사용 및 퀵슬롯 연결여부에 따른 행동을합니다.
 *  인벤토리에 있는 아이템을 사용 후, UI를 새로고침 합니다.
 *  @param SlotNum : 사용할 인벤토리의 슬롯넘버입니다.
 */
void UInventoryComponent::UseItem(int32 Index)
{
	IUseable* UseAbleItem = Cast<IUseable>(Items[Index]);
	if(UseAbleItem==nullptr)
		return;

	UseAbleItem->UseItem(ComponentOwner);
	UpdateSlot(Index);
	
	// IUseable* UseableItem = Cast<IUseable>(Inventory[SlotNum]);
	//
	// if(UseableItem==nullptr || Inventory[SlotNum] ==nullptr ||SlotNum == NOT_INITIALIZED_SLOT)
	// 	return;

	// switch (Inventory[SlotNum])
	// {
	// case EItemType::Armor:
	// case EItemType::Weapon:
	// 	{		
	// 		//UseableItem->UseItem_Implementation(ComponentOwner);
	// 		
	// 		AEquipmentItem* EquipItem = dynamic_cast<AEquipmentItem*>(Inventory[SlotNum]);
	// 		if(EquipItem !=nullptr)
	// 		{
	// 			AddItemToEquipments(EquipItem);
	// 			Inventory[SlotNum]=nullptr;
	// 			InventoryUI->RefreshSlotByIndex(SlotNum);
	// 		}
	// 		break;
	// 	}
	// case EItemType::Tool:
	// 	{
	// 		//UseableItem->UseItem_Implementation(ComponentOwner);
	// 	
	// 		if (Inventory[SlotNum]->ReferenceSlot.IsEmpty())
	// 		{
	// 			// if (NumOfRemainingItem == 0)
	// 			// {
	// 			// 	Inventory[SlotNum] = nullptr;
	// 			// }
	// 			InventoryUI->RefreshSlotByIndex(SlotNum);
	// 		}
	// 		else
	// 		{
	// 			TArray<USlot*> TempSlot;
	// 			for (USlot* eachSlot : Inventory[SlotNum]->ReferenceSlot)
	// 			{
	// 				TempSlot.Add(eachSlot);
	// 			}
	// 			// if (NumOfRemainingItem == 0)
	// 			// {
	// 			// 	Inventory[SlotNum] = nullptr;
	// 			// }
	// 			for (USlot* eachSlot : TempSlot)
	// 			{
	// 				if (eachSlot != nullptr)
	// 				{
	// 					eachSlot->Refresh();
	// 				}
	// 			}
	// 			InventoryUI->RefreshAllSlot();
	// 		}
	// 		break;
	// 	}
	// }
}

/**
 * 해당 인덱스의 아이템이 셀 수 있는 아이템인지 확인합니다.
 */
bool UInventoryComponent::IsItemStackable(int32 Index)
{
	return Items[Index]->NumericData.IsStackable;
}

int8 UInventoryComponent::IndexNormalize(int32 Index)
{
	return Index%16;
}











