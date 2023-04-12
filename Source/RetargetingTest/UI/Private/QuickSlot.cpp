// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/UI/Public/QuickSlot.h"

#include "Blueprint/WidgetTree.h"
#include "Kismet/GameplayStatics.h"
#include "RetargetingTest/UI/Public/Slot.h"
#include "RetargetingTest/Player/Public/CharacterBase.h"

void UQuickSlot::Init()
{
	Character=Cast<ACharacterBase>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));Slots.Init(nullptr,MAX_QUICK_SLOT);
	TArray<UWidget*> widgets;
	WidgetTree->GetAllWidgets(widgets);

	USlot* slot =nullptr;
	for(UWidget* widget : widgets)
	{
		slot = Cast<USlot>(widget);

		if(!slot)
		{
			continue;
		}

		slot->SetType(ESlotType::SLOT_QUICK);
		slot->SetCharacter(this->Character);
		slot->Init();
		Slots[slot->SlotNum]=slot;
	}

	
}

/**
 *  번호에 해당하는 퀵슬롯을 사용하도록 합니다.
 */
void UQuickSlot::Use(int UsedSlotIdx)
{
	Slots[UsedSlotIdx]->Action();
}

void UQuickSlot::SetCharacter(ACharacterBase* NewCharacter)
{
	Character=NewCharacter;
}
