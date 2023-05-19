// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/InventoryManagerComponent.h"

#include "Controller/MyPlayerController.h"
#include "Object/ItemBase.h"
#include "Player/CharacterBase.h"
#include "UI/Inventory.h"
#include "UI/PlayerHUD.h"
#include "UI/Slot.h"

// Sets default values for this component's properties
UInventoryManagerComponent::UInventoryManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	// ...
}

bool UInventoryManagerComponent::AddItemToInventory(AItemBase* Item)
{
	if (Item != nullptr)
	{
		const int32 AvaliableSlot = OwnerInventory.Find(nullptr);
		if (AvaliableSlot != INDEX_NONE)
		{
			OwnerInventory[AvaliableSlot] = Item;
			return true;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,TEXT("You cant carry any more items"));
		}
	}
	return false;
}

void UInventoryManagerComponent::UseItemAtInventorySlot(int32 SlotNum)
{
	if (OwnerInventory[SlotNum] != nullptr && SlotNum != -1)
	{
		TArray<USlot*> TempSlot;

		OwnerInventory[SlotNum]->UseItem(ComponentOwner);

		//레퍼런스 슬롯이 없다면 인벤토리만 갱신합니다.
		if (OwnerInventory[SlotNum]->ReferenceSlot.IsEmpty())
		{
			if (OwnerInventory[SlotNum]->GetCount() == 0)
			{
				OwnerInventory[SlotNum] = nullptr;
			}
			//TODO : 인벤토리를 사용 후 갱신해야할때, 너무 경로가 긴거같음.
			InventoryUI->RefreshAllSlot();
		}
		//있다면 레퍼런스 슬롯을 옮겨줍니다.
		else
		{
			for (USlot* eachSlot : OwnerInventory[SlotNum]->ReferenceSlot)
			{
				TempSlot.Add(eachSlot);
			}
			if (OwnerInventory[SlotNum]->GetCount() == 0)
			{
				OwnerInventory[SlotNum] = nullptr;
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

void UInventoryManagerComponent::SetOwnerInventory(TArray<AItemBase*>& NewInventory)
{
	OwnerInventory=NewInventory;
}


// Called when the game starts
void UInventoryManagerComponent::BeginPlay()
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

