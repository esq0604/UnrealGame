// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/UI/Public/Inventory.h"

#include "Blueprint/WidgetTree.h"
#include "Kismet/GameplayStatics.h"
#include "RetargetingTest/UI/Public/Slot.h"

void UInventory::NativeConstruct()
{
	Super::NativeConstruct();

}

/**
 * 인벤토리의 초기화 부분입니다. 각 슬롯에 타입을 인벤토리 타입으로 지정해줍니다.
 */
void UInventory::Init()
{
	Character=Cast<ARetargetingTestCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	TArray<UWidget*> Widgets;
	WidgetTree->GetAllWidgets(Widgets);
	Slots.Init(nullptr,12);

	for(UWidget* widget : Widgets)
	{
		USlot* slot =nullptr;
		slot = Cast<USlot>(widget);
		if(slot != nullptr)
		{
			slot->SetType(ESlotType::SLOT_INVENTORY);
			slot->SetCharacter(this->Character);
			slot->Init();
			Slots[slot->GetIndex()]=slot;
			
		}
	}
}

void UInventory::Refresh()
{
	for(USlot* slot : Slots)
	{
		slot->Refresh();
	}
}

void UInventory::SetCharacter(ARetargetingTestCharacter* NewCharacter)
{
	Character= NewCharacter;
}

