// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/UI/Public/Slot.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "RetargetingTest/Object/Public/PickUp.h"
#include "RetargetingTest/Object/Public/SlotDragDrop.h"
#include "RetargetingTest/Player/Public/RetargetingTestCharacter.h"


void USlot::NativeConstruct()
{
	Super::NativeConstruct();
}

void USlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if(OutOperation ==nullptr)
	{
		USlotDragDrop* oper =NewObject<USlotDragDrop>();
		oper->From =this;
		oper->Character=this->Character;
		OutOperation=oper;

		if (DragVisualClass != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Drag : DragVisualClass!= nullptr "));

			USlot* visual = CreateWidget<USlot>(Cast<APlayerController>(Character->Controller), DragVisualClass);
			visual->SlotType = this->SlotType;
			visual->Character = this->Character;
			visual->Index = this->Index;
			visual->Refresh();
			
			oper->DefaultDragVisual = visual;
		}
	}
}

bool USlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	USlotDragDrop* Operator = Cast<USlotDragDrop>(InOperation);

	if (Operator != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("NatvieOnDrop : oper != nullptr"));
		Operator->Drop(this);
		return true;
	}
	else
		return false;
}

/**
 * 마우스의 클릭을 감지하는 함수입니다. 우클릭시 사용을하고 ,좌클릭시 드래그인지 감지하고 드래그함수를 호출합니다.
 */
FReply USlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply;
	reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if(InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton)==true)
	{
		// if(Index<0 || Character->GetItemAtInventory(Index)->GetItemType() !=EItemType::ITEM_None)
		// {
		// 	return reply.NativeReply;
		// 	
		// }
		//아이템을 사용하는 함수가 나타납니다.
	}
	else if(InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton)==true)
	{
		if(Character->GetItemAtInventory(Index)!=nullptr)
		{
			if(Character->GetItemAtInventory(Index)->GetItemType() !=EItemType::ITEM_None)
			{
				reply=UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent,this,EKeys::LeftMouseButton);
			}
		}
	}
	return reply.NativeReply;
}

/**
 * 슬롯의 초기화 입니다. 슬롯에 부여된 번호를 인덱스로 지정합니다.
 */
void USlot::Init()
{
	switch (SlotType)
	{
	case ESlotType::SLOT_INVENTORY:
	case ESlotType::SLOT_QUICK:
		Index=SlotNum;
		break;
	}
}

/**
 * 플레이어의 인벤토리를 참조하여 썸네일을 변경합니다.
 */
void USlot::Refresh()
{
	switch(SlotType)
	{
	case ESlotType::SLOT_INVENTORY:
		{
			UTexture2D* Tex=Character->GetThumnailAtInventorySlot(Index);
			Img->SetBrushFromTexture(Tex);
			Text->SetVisibility(ESlateVisibility::Hidden);
			break;
		}
	case ESlotType::SLOT_QUICK:
		{
		
			UTexture2D* Tex=Character->GetThumnailAtInventorySlot(Index);
			Img->SetBrushFromTexture(Tex);
			Text->SetVisibility(ESlateVisibility::Hidden);
			break;
			

		}
	}
}

void USlot::SetType(ESlotType NewSlotType)
{
	SlotType=NewSlotType;
}

void USlot::SetCharacter(ARetargetingTestCharacter* NewCharacter)
{
	Character=NewCharacter;
}

void USlot::SetIndex(int32 NewIndex)
{
	Index=NewIndex;
}

void USlot::SetImg(UTexture2D* NewImg)
{
	Img->SetBrushFromTexture(NewImg);
}

ESlotType USlot::GetSlotType() const
{
	return SlotType;
}

int32 USlot::GetSlotIndex() const
{
	return Index;
}
