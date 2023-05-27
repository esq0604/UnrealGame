// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/InventoryComponent.h"

#include "Controller/MyPlayerController.h"
#include "Object/ItemBase.h"
#include "Player/CharacterBase.h"
#include "UI/Inventory.h"
#include "UI/PlayerHUD.h"
#include "UI/Slot.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	// ...
	ComponentOwner=Cast<ACharacterBase>(GetOwner());
}

bool UInventoryComponent::AddItemToInventory(AItemBase* Item)
{
	if (Item != nullptr)
	{
		const int32 AvaliableSlot = Inventory.Find(nullptr);
		if (AvaliableSlot != INDEX_NONE)
		{
			Inventory[AvaliableSlot] = Item;
			Inventory[AvaliableSlot]=Item;

			if(Inventory[AvaliableSlot]==nullptr)
				UE_LOG(LogTemp,Warning,TEXT("Character Inven[AvaliableSlot nullptr"));

			InventoryUI->RefreshSlotByIndex(AvaliableSlot);
			
			return true;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,TEXT("You cant carry any more items"));
		}
	}
	return false;
}

void UInventoryComponent::UseItemAtInventorySlot(int32 SlotNum)
{
	if (Inventory[SlotNum] != nullptr && SlotNum != -1)
	{
		TArray<USlot*> TempSlot;

		Inventory[SlotNum]->UseItem(ComponentOwner);

		//레퍼런스 슬롯이 없다면 인벤토리만 갱신합니다.
		if (Inventory[SlotNum]->ReferenceSlot.IsEmpty())
		{
			if (Inventory[SlotNum]->GetCount() == 0)
			{
				Inventory[SlotNum] = nullptr;
			}
			//TODO : 인벤토리를 사용 후 갱신해야할때, 너무 경로가 긴거같음.
			InventoryUI->RefreshSlotByIndex(SlotNum);
		}
		//있다면 레퍼런스 슬롯을 옮겨줍니다.
		else
		{
			for (USlot* eachSlot : Inventory[SlotNum]->ReferenceSlot)
			{
				TempSlot.Add(eachSlot);
			}
			if (Inventory[SlotNum]->GetCount() == 0)
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
			//TODO : 인벤토리를 사용 후 갱신해야할때, 너무 경로가 긴거같음.
			InventoryUI->RefreshAllSlot();
		}
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

UTexture2D* UInventoryComponent::GetThumbnailAtInventorySlot(int32 SlotIdx) const
{
	return Inventory[SlotIdx]->PickupThumbnail;
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	const ACharacterBase* Character=Cast<ACharacterBase>(GetOwner());
	const AMyPlayerController* PC = Cast<AMyPlayerController>(Character->GetController());
	if(PC!=nullptr)
	{
		const UPlayerHUD* newPlayerHUD=PC->GetPlayerHUD();
		if(newPlayerHUD!=nullptr)
		{
			InventoryUI=newPlayerHUD->GetInventory();
		}
	}
}

