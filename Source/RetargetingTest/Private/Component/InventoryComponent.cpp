// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/InventoryComponent.h"

#include "Controller/MyPlayerController.h"
#include "Data/ItemDataAsset.h"
#include "Data/PotionDataAsset.h"
#include "Interface/Useable.h"
#include "Object/EquipmentItem.h"
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
	ArmorItems.Init(nullptr,16);
	WeaponItems.Init(nullptr,16);
	ToolItems.Init(nullptr,16);
	MagicItems.Init(nullptr,16);
	QuestItems.Init(nullptr,16);
	

}

TArray<UItemDataAsset*>& UInventoryComponent::GetItemsRef(EItemType Type) 
{
	switch (Type)
	{
	case EItemType::Armor:
		return ArmorItems;
	case EItemType::Magic:
		return MagicItems;
	case EItemType::Quest:
		return QuestItems;
	case EItemType::Tool:
		return ToolItems;
	case EItemType::Weapon:
		return WeaponItems;
	default:
		static TArray<UItemDataAsset*> Empty;
		return Empty;
	}
}

UItemDataAsset* UInventoryComponent::GetItem(EItemType Type, int32 Index) 
{
	return GetItemsRef(Type)[Index];
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
		UE_LOG(LogTemp,Warning,TEXT("Item Name : %s"),*Item->GetName());
		
		if(Item!=nullptr)
		{
			const int AvailAbleIndex= GetItemsRef(Item->ItemType).Find(nullptr);
			
			//장비 아이템은 스폰하여 플레이어에게 장착시키도록합니다.
			if(Item->ItemType==EItemType::Armor || Item->ItemType==EItemType::Weapon)
			{
				FActorSpawnParameters Parameters;
				Parameters.Instigator=ComponentOwner;
				Parameters.Owner=ComponentOwner;
				FVector SpawnLocation = ComponentOwner->GetActorLocation();
				FTransform SpawnTransform(ComponentOwner->GetActorRotation(),SpawnLocation);
				
				AEquipmentItem* EquipmentItem = GetWorld()->SpawnActor<AEquipmentItem>(Item->ActorToSpawn,SpawnTransform,Parameters);
				//EquipmentItem->SetItemData(MakeItem);
				EquipmentItem->SetOwner(GetOwner());
				EquipmentItem->Equip(ComponentOwner,Item);
			}
			else
			{
				AddItem(Item);
				UpdateSlot(Item->ItemType,AvailAbleIndex);
			}
			//인벤토리 UI를 갱신합니다.
		}
		else
		{
			UE_LOG(LogTemp,Warning,TEXT("MakeItem nullptr"));
		}
	}
}

/**
 * @brief 슬롯의 Index를 입력받아 InventoryUI를 업데이트합니다.
 * @param Index Update할 슬롯의 Index입니다.
 */
void UInventoryComponent::UpdateSlot(EItemType Type,int32 Index)
{
	const UItemDataAsset* Item = GetItem(Type,Index);

	if(Item!=nullptr)
	{
		
		InventoryUI->SetTexture(Type,IndexNormalize(Index),Item->AssetData.Icon);
		if(Item->NumericData.Quantity==0)
		{
			GetItemsRef(Type)[Index]=nullptr;
			InventoryUI->RemoveItem(Type,IndexNormalize(Index));
		}
		else
		{
			if(Item->NumericData.IsStackable)
			{
				InventoryUI->SetAmountText(Type,IndexNormalize(Index),Item->NumericData.Quantity);
				
			}
			else
			{
				InventoryUI->HideAmountText(Type,IndexNormalize(Index));		
			}
		}
	}
	else
	{
		InventoryUI->RemoveItem(Type,IndexNormalize(Index));
	}
}

bool UInventoryComponent::AddItem(UItemDataAsset* AddedItem)
{
	if(AddedItem!=nullptr)
	{
		const int32 AvailableIndex=GetItemsRef(AddedItem->ItemType).Find(nullptr);
		 GetItemsRef(AddedItem->ItemType)[AvailableIndex]=AddedItem;
		return true;
	}
	return false;
}

/**
 *  인벤토리에있는 아이템을사용합니다. 장비아이템의 경우 장착을하고, 소비아이템인경우 사용 및 퀵슬롯 연결여부에 따른 행동을합니다.
 *  인벤토리에 있는 아이템을 사용 후, UI를 새로고침 합니다.
 *  @param SlotNum : 사용할 인벤토리의 슬롯넘버입니다.
 */
bool UInventoryComponent::UseItem(EItemType Type,int32 Index)
{
	IUseable* UseableItem = Cast<IUseable>(GetItem(Type,Index));
	bool result=false;

	if(UseableItem!=nullptr)
	{
		result= UseableItem->UseItem(ComponentOwner);
		if(result)
		{
			UpdateSlot(Type,Index);
		}
		return result;
	}

	return result;
}

/**
 * 해당 인덱스의 아이템이 셀 수 있는 아이템인지 확인합니다.
 */
bool UInventoryComponent::IsItemStackable(int32 Index)
{
	return true;
}

bool UInventoryComponent::IsItemInSlotValid(int32 Index) const
{
	return true;
}

int8 UInventoryComponent::IndexNormalize(int32 Index)
{
	return Index%16;
}











