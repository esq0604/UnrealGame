// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/InventoryComponent.h"

#include "Controller/MyPlayerController.h"
#include "Data/ItemDataAsset.h"
#include "Interface/Useable.h"
#include "Object/EquipmentItem.h"
#include "Object/SpawnedItem.h"
#include "Player/CharacterBase.h"
#include "UI/InventoryUI.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	// ...

	//melee weapon, tool, pants,chest, shoes, quest
	ArmorItemsContainer.Init(nullptr,InventorySize);
	WeaponItemsContainer.Init(nullptr,InventorySize);
	ToolItemsContainer.Init(nullptr,InventorySize);
	MagicItemsContainer.Init(nullptr,InventorySize);
	QuestItemsContainer.Init(nullptr,InventorySize);
	//QuickItems.Init(nullptr,5);
}

TArray<UItemDataAsset*>& UInventoryComponent::GetItemsContainerRef(EItemType Type) 
{
	switch (Type)
	{
	case EItemType::Armor:
		return ArmorItemsContainer;
	case EItemType::Magic:
		return MagicItemsContainer;
	case EItemType::Quest:
		return QuestItemsContainer;
	case EItemType::Tool:
		return ToolItemsContainer;
	case EItemType::Weapon:
		return WeaponItemsContainer;
	default:
		static TArray<UItemDataAsset*> Empty;
		return Empty;
	}
}

UItemDataAsset* UInventoryComponent::GetItem(EItemType Type, int32 Index) 
{
	return GetItemsContainerRef(Type)[Index];
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	ComponentOwner=Cast<ACharacterBase>(GetOwner());
	
	AddStartingItem();
}

/**
 * @brief 슬롯의 Index를 입력받아 InventoryUI를 업데이트합니다.
 * @param Index 아이템 Container의 Type과 Index가 들어옵니다.
 */
void UInventoryComponent::UpdateInventoryUI(EItemType Type,int32 Index)
{
	const UItemDataAsset* Item = GetItem(Type,Index);
	if(!InventoryUI.IsValid())
	{
		UE_LOG(LogTemp,Warning,TEXT("InvenUI is not valid"));
		return;
	}
	if(Item!=nullptr)
	{
		InventoryUI->UpdatePanel(Type,Index);
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Item Remove"));

		InventoryUI->RemoveItem(Type,Index);
	}
}

void UInventoryComponent::AddItemToIndex(UItemDataAsset* Item, int32 Index)
{
	
}

/**
 * @brief 아이템을 타입에 맞는 저장소에 넣도록합니다.
 * @param AddedItem 넣을 아이템이 들어옵니다.
 * @return 성공여부입니다.
 */
bool UInventoryComponent::AddItem(const UItemDataAsset* AddedItem)
{
	//아이템 종류가 같은 아이템이 있는지 확인합니다.
	if(!AddedItem)
	{
		return false;
	}
	const int32 EqualItemIndex = HasEqualItem(AddedItem->ID,AddedItem->ItemType);
	if(EqualItemIndex != INDEX_NONE)
	{
		//Stackable한지 확인합니다.
		if(AddedItem->NumericData.IsStackable)
		{
			//기존아이템이 있던자리를 업데이트합니다. MaxStack을 초과하는지 확인합니다.
			GetItem(AddedItem->ItemType,EqualItemIndex)->NumericData.Quantity += AddedItem->NumericData.Quantity;
			//UpdateInventoryUI(AddedItem->ItemType,EqualItemIndex);
			return true;
		}
	}
		
	//빈 공간에 새 아이템을 추가합니다.
	const int32 AvailableIndex=GetItemsContainerRef(AddedItem->ItemType).Find(nullptr);
	if(AvailableIndex==INDEX_NONE)
	{
		return false;
	}
	GetItemsContainerRef(AddedItem->ItemType)[AvailableIndex]=const_cast<UItemDataAsset*>(AddedItem);
	UpdateInventoryUI(AddedItem->ItemType,AvailableIndex);
	return true;
}

bool UInventoryComponent::AddStartingItem()
{
	for(const UItemDataAsset* Item : StartingItems)
	{
		const UItemDataAsset* DuplicatedItem = DuplicateObject(Item,this);
		
		if(DuplicatedItem!=nullptr)
		{
			//장비아이템의 종류일 경우 아이템을 장착합니다.
			if(DuplicatedItem->ItemType==EItemType::Weapon ||
				DuplicatedItem->ItemType==EItemType::Armor ||
				DuplicatedItem->ItemType==EItemType::Shoes ||
				DuplicatedItem->ItemType==EItemType::Gauntlet)
			{
				FActorSpawnParameters Parameters;
				//Parameters.Instigator=GetOwner();
				Parameters.Owner=GetOwner();
				
				const FVector SpawnLocation = GetOwner()->GetActorLocation();
				const FTransform SpawnTransform(GetOwner()->GetActorRotation(),SpawnLocation);
				AEquipmentItem* EquipmentItem = GetWorld()->SpawnActor<AEquipmentItem>(DuplicatedItem->ActorToSpawn,SpawnTransform,Parameters);

				EquipmentItem->SetOwner(GetOwner());
				AddItem(DuplicatedItem);
				EquipmentItem->Equip(ComponentOwner,DuplicatedItem);
			}
			else
			{
				AddItem(DuplicatedItem);
			}
		}
	}

	return false;
}

int32 UInventoryComponent::HasEqualItem(FText ItemID, EItemType Type)
{
	const TArray<UItemDataAsset*> Datas =GetItemsContainerRef(Type);

	int32 Index=0;
	for(const UItemDataAsset* Data : Datas)
	{
		if(!Data)
		{
			Index++;
			continue;
		}
		if(Data->ID.EqualTo(ItemID))
		{
			return Index;	
		}
		
		Index++;
	}
	
	return INDEX_NONE;
}

/**
 * @brief 슬롯의 아이템을 사용합니다.
 * @param Type 사용할 아이템의 타입입니다.
 * @param Index 사용할 아이템이 저장된 인덱스입니다.
 * @return 성공여부입니다.
 */
bool UInventoryComponent::UseItem(EItemType Type,int32 Index)
{
	UItemDataAsset* ItemData = GetItem(Type,Index);
	IUseable* UseableItem = Cast<IUseable>(ItemData);
	if(UseableItem==nullptr)
	{
		return false;
	}
	bool result=false;
	result= UseableItem->UseItem(ComponentOwner);
	
	if(ItemData->NumericData.Quantity==0)
	{
		GetItemsContainerRef(Type)[Index]=nullptr;
	}
	InventoryUI->UpdatePanel(Type,Index);
	return result;
}

bool UInventoryComponent::DropItem(EItemType Type, int32 Index)
{
	UItemDataAsset* SpawnDataAsset =GetItem(Type,Index);
	const FVector SpawnLoc = GetOwner()->GetActorLocation()+GetOwner()->GetActorForwardVector()*100.f;
	const FRotator SpawnRot = GetOwner()->GetActorRotation();
	ASpawnedItem* SpawnItem =GetWorld()->SpawnActor<ASpawnedItem>(SpawnDataAsset->ActorToSpawn,SpawnLoc,SpawnRot);
	SpawnItem->SetDataAsset(SpawnDataAsset);
	
	GetItemsContainerRef(Type)[Index]=nullptr;
	InventoryUI->UpdatePanel(Type,Index);
	return true;
}

/**
 * 해당 인덱스의 아이템이 셀 수 있는 아이템인지 확인합니다.
 */
bool UInventoryComponent::IsItemStackable(EItemType Type, int32 Index)
{
	return GetItem(Type,Index)->NumericData.IsStackable;
}

bool UInventoryComponent::IsItemInSlotValid(EItemType Type,int32 Index)
{
	return GetItem(Type,Index)!=nullptr;
}









