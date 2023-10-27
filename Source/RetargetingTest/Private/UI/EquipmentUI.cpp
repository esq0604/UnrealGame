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
	const ACharacter* Character = GetOwningPlayer()->GetCharacter();
	UInventoryComponent* InventoryComp = Cast<UInventoryComponent>(
		Character->GetComponentByClass(UInventoryComponent::StaticClass()));
	//Slots.Init(nullptr, InventoryComp->GetEquipments().Num());


	WeaponSlot->SetEquipItemType();
	HeadSlot->SetEquipItemType();
	ArmorSlot->SetEquipItemType();
	PantsSlot->SetEquipItemType();
	SlotInit(WeaponSlot);
	SlotInit(HeadSlot);
	SlotInit(ArmorSlot);
	SlotInit(PantsSlot);
}

void UEquipmentUI::SlotInit(UEquipmentSlot* EquipSlot)
{
	EquipSlot->SetType(ESlotType::SLOT_EQUIP);
	EquipSlot->SetInventoryComponent(InventoryComponent);
	EquipSlot->Init();
	//Slots[static_cast<int32>(EquipSlot->GetEquipItemType())] = EquipSlot;
}

bool UEquipmentUI::Initialize()
{
	bool success = Super::Initialize();
	if (!CloseButton)
	{
		return false;
	}

	CloseButton->OnClicked.AddDynamic(this, &UEquipmentUI::CloseButtonClicked);

	return success;
}

void UEquipmentUI::RefreshAllSlot()
{
	for (UEquipmentSlot* slot : Slots)
	{
		slot->Refresh();
	}
}

void UEquipmentUI::RefreshSlotByIndex(int32 Index)
{
	Slots[Index]->Refresh();
}

void UEquipmentUI::RefreshSlotByEquipmentType()
{
	const ACharacter* Character = GetOwningPlayer()->GetCharacter();
	UInventoryComponent* InventoryComp = Cast<UInventoryComponent>(
		Character->GetComponentByClass(UInventoryComponent::StaticClass()));
	//TArray<AItemBase*> Inventory = InventoryComp->GetInventory();
//	TArray<AEquipmentItem*> Equipments = InventoryComp->GetEquipments();

//	UTexture2D* Tex = InventoryComp->GetThumbnailAtEquipment();
	const UEquipmentSlot* TempSlot = GetSlot();
	// if (Tex)
	// {
	// 	TempSlot->Img->SetBrushFromTexture(Tex);
	// }
	// else
	// {
	// 	TempSlot->Img->SetBrushFromTexture(TempSlot->DefaultTexture);
	// }
}

void UEquipmentUI::SetInventoryComponent(UInventoryComponent* NewInventoryComponent)
{
	InventoryComponent=NewInventoryComponent;
}


UEquipmentSlot* UEquipmentUI::GetSlot()
{
	for (UEquipmentSlot* TempSlot : Slots)
	{
		if (TempSlot != nullptr)
		{
			// if (TempSlot->GetEquipItemType())
			// {
			// 	return TempSlot;
			// }
		}
	}
	return nullptr;
}
