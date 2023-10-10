// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/InventoryComponent.h"

#include "Controller/MyPlayerController.h"
#include "Interface/Countable.h"
#include "Interface/Useable.h"
#include "Object/ItemBase.h"
#include "Object/EquipmentItem.h"
#include "Player/CharacterBase.h"
#include "UI/EquipmentUI.h"
#include "UI/InventoryUI.h"
#include "UI/Slot.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	// ...
	Equipments.Init(nullptr,4);
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
	ComponentOwner=Cast<ACharacterBase>(GetOwner());
	const AMyPlayerController* PC = Cast<AMyPlayerController>(ComponentOwner->GetController());
	if(ensure(PC))
	{
		InventoryUI = PC->GetInventoryUI();
		EquipmentUI = PC->GetEquipmentUI();
	}

	for(TSubclassOf<AItemBase> StartItem : StartItems)
	{
		FActorSpawnParameters SpawnParameters;
		AddItemToInventory(Cast<AItemBase>(GetWorld()->SpawnActor(StartItem,nullptr,nullptr,SpawnParameters)));

	}
}

bool UInventoryComponent::AddItemToInventory(AItemBase* AddedItem)
{
	if (AddedItem != nullptr)
	{
		const int32 AvaliableSlot = Inventory.Find(nullptr);
		if (AvaliableSlot != INDEX_NONE)
		{
			Inventory[AvaliableSlot] = AddedItem;
			InventoryUI->RefreshSlotByIndex(AvaliableSlot);
			return true;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,TEXT("Item null ptr"));
		}
	}
	return false;
}

bool UInventoryComponent::AddItemToEquipment(AItemBase* AddedItem)
{
	if (AddedItem != nullptr)
	{
		const int32 AvaliableSlot = Equipments.Find(nullptr);
		if (AvaliableSlot != INDEX_NONE)
		{
			//Equipment[AvaliableSlot] = AddedItem;
			//Equipment[AvaliableSlot]=AddedItem;

			if(Equipments[AvaliableSlot]==nullptr)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,TEXT("You cant carry any more items"));
				return false;
			}
			EquipmentUI->RefreshSlotByIndex(AvaliableSlot);
			return true;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,TEXT("Item null ptr"));
		}
	}
	return false;
}

/**
 *  인벤토리에있는 아이템을사용합니다. 장비아이템의 경우 장착을하고, 소비아이템인경우 사용 및 퀵슬롯 연결여부에 따른 행동을합니다.
 *  인벤토리에 있는 아이템을 사용 후, UI를 새로고침 합니다.
 *  @param SlotNum : 사용할 인벤토리의 슬롯넘버입니다.
 */
void UInventoryComponent::UseItemAtInventorySlot(int32 SlotNum)
{
	IUseable* UseableItem = Cast<IUseable>(Inventory[SlotNum]);
	ICountable* CountableItem = Cast<ICountable>(Inventory[SlotNum]);

	if(UseableItem==nullptr || Inventory[SlotNum] ==nullptr ||SlotNum == NOT_INITIALIZED_SLOT)
		return;

	switch (Inventory[SlotNum]->ItemType)
	{
	case EItemType::ITEM_EQUIPMENT:
		{		

			if(ComponentOwner!=nullptr)
				UseableItem->UseItem_Implementation(ComponentOwner);

			
			AEquipmentItem* EquipItem = dynamic_cast<AEquipmentItem*>(Inventory[SlotNum]);
			if(EquipItem !=nullptr)
			{
				Equipments[static_cast<int32>(EquipItem->GetEquipItemType())]=EquipItem;
				Inventory[SlotNum]=nullptr;
				InventoryUI->RefreshSlotByIndex(SlotNum);
				EquipmentUI->RefreshSlotByEquipmentType(EquipItem->GetEquipItemType());
			}
			break;
		}
	case EItemType::ITEM_CONSUME:
		{
			UseableItem->UseItem_Implementation(ComponentOwner);
			const int32 NumOfRemainingItem = CountableItem->GetCount_Implementation();
		
			if (Inventory[SlotNum]->ReferenceSlot.IsEmpty())
			{
				if (NumOfRemainingItem == 0)
				{
					Inventory[SlotNum] = nullptr;
				}
				InventoryUI->RefreshSlotByIndex(SlotNum);
			}
			else
			{
				TArray<USlot*> TempSlot;
				for (USlot* eachSlot : Inventory[SlotNum]->ReferenceSlot)
				{
					TempSlot.Add(eachSlot);
				}
				if (NumOfRemainingItem == 0)
				{
					Inventory[SlotNum] = nullptr;
				}
				for (USlot* eachSlot : TempSlot)
				{
					if (eachSlot != nullptr)
					{
						eachSlot->Refresh();
					}
				}
				InventoryUI->RefreshAllSlot();
			}
			break;
		}
	}
}

/**
 * Equipment UI의 슬롯을 사용합니다.
 * 장비장착을 해제하고 인벤토리에 넣도록합니다.
 * @param SlotNum : 사용할 슬롯의 인덱스입니다.
 */
void UInventoryComponent::UseItemAtEquipmentSlot(int32 SlotNum,EEquipment_Type EquipmentType)
{
	
	IUseable* UseableItem= Cast<IUseable>(GetItemAtEquipments(EquipmentType));
	if(UseableItem)
	{
		UseableItem->UseItem_Implementation(ComponentOwner);
			
		Inventory[SlotNum] = GetItemAtEquipments(EquipmentType);
		Equipments[static_cast<int32>(GetItemAtEquipments(EquipmentType)->GetEquipItemType())] =nullptr;
		EquipmentUI->RefreshSlotByEquipmentType(EquipmentType);
		InventoryUI->RefreshSlotByIndex(SlotNum);
	}
	
	
}

AItemBase* UInventoryComponent::GetItemAtInventory(int32 SlotNum) const
{
	return Inventory[SlotNum];
}

TArray<AItemBase*> UInventoryComponent::GetInventory() const
{
	return Inventory;
}

TArray<AEquipmentItem*> UInventoryComponent::GetEquipments() const
{
	return Equipments;
}

AEquipmentItem* UInventoryComponent::GetItemAtEquipments(EEquipment_Type EquipmentType) const
{
	for(AEquipmentItem* Item : Equipments)
	{
		if(Item!=nullptr)
		{
			if(Item->GetEquipItemType()==EquipmentType)
			{
				return Item;
			}
		}
	}

	return nullptr;
}

UTexture2D* UInventoryComponent::GetThumbnailAtInventorySlot(int32 SlotIdx) const
{
	
	if(Inventory[SlotIdx])
	{
		return Inventory[SlotIdx]->PickupThumbnail;
	}

	return nullptr;
}

UTexture2D* UInventoryComponent::GetThumbnailAtEquipment(EEquipment_Type Type) const
{
	AEquipmentItem* Item = GetItemAtEquipments(Type);
	if(Item!=nullptr)
		return Item->GetThumbnail();

	return nullptr;
}




