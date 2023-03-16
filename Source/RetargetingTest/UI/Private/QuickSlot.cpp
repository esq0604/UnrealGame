// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/UI/Public/QuickSlot.h"

#include "Blueprint/WidgetTree.h"
#include "Kismet/GameplayStatics.h"
#include "RetargetingTest/Player/Public/CharaterAnimInstance.h"
#include "RetargetingTest/UI/Public/Slot.h"
#include "RetargetingTest/Player/Public/RetargetingTestCharacter.h"
#include "Widgets/Text/ISlateEditableTextWidget.h"

void UQuickSlot::Init()
{
	Character=Cast<ARetargetingTestCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));Slots.Init(nullptr,MAX_QUICK_SLOT);
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
 *  
 */
void UQuickSlot::Use(int index)
{
	Slots[index-1]->Action();
}
