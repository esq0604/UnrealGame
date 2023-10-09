// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/EquipmentUI.h"

#include "Blueprint/WidgetTree.h"
#include "Component/InventoryComponent.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Object/EquipmentItem.h"
#include "Player/CharacterBase.h"
#include "UI/EquipmentSlot.h"


void UEquipmentUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void UEquipmentUI::CloseButtonClicked()
{
	SetVisibility(ESlateVisibility::Hidden);
}



/**
 * UI의 각 슬롯의 타입을 지정해줍니다.
 * 
 */
void UEquipmentUI::Init()
{
	const ACharacter* Character=GetOwningPlayer()->GetCharacter();
	UInventoryComponent* InventoryComp =Cast<UInventoryComponent>(Character->GetComponentByClass(UInventoryComponent::StaticClass()));
	Slots.Init(nullptr,InventoryComp->GetEquipments().Num());	


	if(Player)
	{
		WeaponSlot->SetEquipItemType(EEquipment_Type::Weapon);
		HeadSlot->SetEquipItemType(EEquipment_Type::Head);
		ArmorSlot->SetEquipItemType(EEquipment_Type::Armor);
		PantsSlot->SetEquipItemType(EEquipment_Type::Pants);
		SlotInit(WeaponSlot);
		SlotInit(HeadSlot);
		SlotInit(ArmorSlot);
		SlotInit(PantsSlot);
	}
}

void UEquipmentUI::SlotInit(UEquipmentSlot* EquipSlot)
{
	const ACharacter* Character=GetOwningPlayer()->GetCharacter();
	UInventoryComponent* InventoryComp =Cast<UInventoryComponent>(Character->GetComponentByClass(UInventoryComponent::StaticClass()));

	EquipSlot->SetType(ESlotType::SLOT_EQUIP);
	EquipSlot->SetInventoryComponent(InventoryComp);
	EquipSlot->Init();
	Slots[static_cast<int32>(EquipSlot->GetEquipItemType())]=EquipSlot;
}

bool UEquipmentUI::Initialize()
{
	bool success=Super::Initialize();
	if(!CloseButton)
		return false;

	CloseButton->OnClicked.AddDynamic(this,&UEquipmentUI::CloseButtonClicked);

	return success;
	
}

void UEquipmentUI::RefreshAllSlot()
{
	for(UEquipmentSlot* slot : Slots)
	{
		slot->Refresh();	
	}
}

void UEquipmentUI::RefreshSlotByIndex(int32 Index)
{
	Slots[Index]->Refresh();	
}

void UEquipmentUI::RefreshSlotByEquipmentType(EEquipment_Type Type)
{
	const ACharacter* Character=GetOwningPlayer()->GetCharacter();
	UInventoryComponent* InventoryComp =Cast<UInventoryComponent>(Character->GetComponentByClass(UInventoryComponent::StaticClass()));
	TArray<AItemBase*> Inventory= InventoryComp->GetInventory();
	TArray<AEquipmentItem*> Equipments= InventoryComp->GetEquipments();

	UTexture2D* Tex= InventoryComp->GetThumbnailAtEquipment(Type);
	const UEquipmentSlot* TempSlot = GetSlot(Type);
	if(Tex)
		TempSlot->Img->SetBrushFromTexture(Tex);
	else
	{
		TempSlot->Img->SetBrushFromTexture(TempSlot->DefaultTexture);
	}
}

void UEquipmentUI::SetCharacter(ACharacterBase* NewCharacter)
{
	Player=NewCharacter;
}

UEquipmentSlot* UEquipmentUI::GetSlot(EEquipment_Type Type)
{
	for(UEquipmentSlot* TempSlot : Slots)
	{
		if(TempSlot!=nullptr)
		{
			if(TempSlot->GetEquipItemType() == Type)
			{
				return TempSlot; 
			}
		}
	}
	return nullptr;
}


