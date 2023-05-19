// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/UI/QuickSlot.h"

#include "Blueprint/WidgetTree.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerBase.h"
#include "RetargetingTest/Public/Player/CharacterBase.h"
#include "RetargetingTest/Public/UI/Slot.h"

void UQuickSlot::Init()
{
	Player=Cast<APlayerBase>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));Slots.Init(nullptr,MAX_QUICK_SLOT);
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
		slot->SetCharacter(this->Player);
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

void UQuickSlot::SetCharacter(ACharacterBase* NewPlayer)
{
	Player=NewPlayer;
}
