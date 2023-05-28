// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Public/UI/Slot.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "RetargetingTest/Public/Object/ItemBase.h"
#include "RetargetingTest/Public/Object/SlotDragDrop.h"
#include "RetargetingTest/Public/Player/CharacterBase.h"


void USlot::NativeConstruct()
{
	Super::NativeConstruct();
	if(Player)
		InventoryComponent=Player->GetInventoryManagerCompnent();
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Slot NativeContruct Player nullptr"));
	}
	if(InventoryComponent)
	{
		UE_LOG(LogTemp,Warning,TEXT("InventoryComp not nullptr"));
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("InventoryComp nullptr"));

	}
}

/**
 * 슬롯 드래그시 보일 드래그슬롯을 만들어 보여줍니다.
 * @param OutOperation - UMG의 기본 드래그 드롭 연산이지만 새로운 Drag Drop클래스를 통해 정의합니다.
 */
void USlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if(OutOperation ==nullptr)
	{
		USlotDragDrop* oper =NewObject<USlotDragDrop>();
		oper->From =this;
		oper->Player=this->Player;
		OutOperation=oper;

		if (DragVisualClass != nullptr)
		{
			USlot* visual = CreateWidget<USlot>(Cast<APlayerController>(Player->Controller), DragVisualClass);
			if(visual!=nullptr)
			{
				visual->SlotType = this->SlotType;
				visual->Player = this->Player;
				visual->Index = this->Index;
				visual->InventoryComponent=Player->GetInventoryManagerCompnent();
				visual->Refresh();
			}
			else
			{
				UE_LOG(LogTemp,Warning,TEXT("visual nullptr"));
			}
			oper->DefaultDragVisual = visual;
		}
	}
}

/**
 * 슬롯을 드래그 중 놓을때 호출됩니다. 드롭한 위치에 따라 인벤토리 스왑, 퀵슬롯 등록, 퀵슬롯 스왑 등 이루어집니다.
 * @param InGeometry - 이벤트를 수신하는 위젯의 지오메트리입니다.
 * @param InDragDropEvent - 위젯에 무언가 놓을때 호출됩니다.
 * @param InOperation - 위젯의 드래그,드롭 작업을 수행합니다.
 */
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
 * @return FReply - 특정 위젯에 대한 마우스 이벤트 처리를 반환합니다. 
 */
FReply USlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply;
	reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if(InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton)==true)
	{
		if(InventoryComponent->GetItemAtInventory(Index) !=nullptr)
		{
			if(Index<0 || InventoryComponent->GetItemAtInventory(Index)!=nullptr)
			{
				InventoryComponent->UseItemAtInventorySlot(Index);
				return reply.NativeReply;
			}
		}
	}
	else if(InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton)==true)
	{
		if(InventoryComponent->GetItemAtInventory(Index)!=nullptr)
		{
			if(InventoryComponent->GetItemAtInventory(Index)!=nullptr)
			{
				reply=UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent,this,EKeys::LeftMouseButton);
			}
		}
	}
	return reply.NativeReply;
}

/**
 * 슬롯의 초기화 입니다. 인벤토리의 경우 슬롯의 번호를 통해 인덱스를 지정합니다.
 * 퀵슬롯의 경우 초기값을 -1로 지정하고, 인벤토리의 아이템이 등록될시 인덱스를 변경합니다.
 */
void USlot::Init()
{
	switch (SlotType)
	{
	case ESlotType::SLOT_INVENTORY:
		Index=SlotNum;
		CountText->SetVisibility(ESlateVisibility::Hidden);
		break;
	case ESlotType::SLOT_QUICK:
		Index=-1;
		CountText->SetVisibility(ESlateVisibility::Hidden);
		break;
	}
}

/**
 * 슬롯의 갱신함수입니다. 아이템이 사용되거나, 위치가 바뀔시 호출됩니다. 
 */
void USlot::Refresh()
{
	if(Player->GetInventoryManagerCompnent()!=nullptr)
	{
		TArray<AItemBase*> Inventory= InventoryComponent->GetInventory();
		switch(SlotType)
		{
		case ESlotType::SLOT_INVENTORY:
			{
				if(Inventory[Index]!=nullptr)
				{
					Count=Inventory[Index]->GetCount();
				}
			
				UTexture2D* Tex= InventoryComponent->GetThumbnailAtInventorySlot(Index);
				if(Tex)
				{
					Img->SetBrushFromTexture(Tex);
				}
				else
				{
					Img->SetBrushFromTexture(DefaultTexture);
				}
				if(Count >1)
				{
					CountText->SetText(FText::FromString(FString::FromInt(Count)));
					CountText->SetVisibility(ESlateVisibility::Visible);
				}
				else
				{
					CountText->SetVisibility(ESlateVisibility::Hidden);
				}
				break;
			}
		case ESlotType::SLOT_QUICK:
			{
				if(Index<0)
				{
					Img->SetBrushFromTexture(nullptr);
					CountText->SetVisibility(ESlateVisibility::Hidden);
					break;
				}
				else
				{
					if(Inventory[Index]!=nullptr)
					{
						Count= Inventory[Index]->GetCount();
					}
					UTexture2D* Tex=InventoryComponent->GetThumbnailAtInventorySlot(Index);
					Img->SetBrushFromTexture(Tex);
					if(Count >1)
					{
						CountText->SetText(FText::FromString(FString::FromInt(Count)));
						CountText->SetVisibility(ESlateVisibility::Visible);
					}
					else
					{
						CountText->SetVisibility(ESlateVisibility::Hidden);
					}
					break;
				}
			}
		default:
			return;
		}
	}
	else
	{
		return;
	}
}

void USlot::SetType(ESlotType NewSlotType)
{
	SlotType=NewSlotType;
}

void USlot::SetCharacter(ACharacterBase* NewCharacter)
{
	Player=NewCharacter;
}

void USlot::SetIndex(int32 NewIndex)
{
	Index=NewIndex;
}

void USlot::SetImg(UTexture2D* NewImg)
{
	Img->SetBrushFromTexture(NewImg);
}

void USlot::SetInventoryCompnent(UInventoryComponent* NewInventoryComponent)
{
	InventoryComponent=NewInventoryComponent;
}

/**
 * 슬롯의 사용 함수입니다. 플레이어에게 슬롯의 인덱스를 넘겨주어 인덱스에 해당하는 아이템을 사용하도록합니다.
 */
void USlot::Action()
{
	switch(SlotType)
	{
	case ESlotType::SLOT_INVENTORY:
	case ESlotType::SLOT_QUICK:
		//Player->UseItemAtInventorySlot(Index);
		break;
		
	default:
		break;
	}

}

ESlotType USlot::GetSlotType() const
{
	return SlotType;
}

int32 USlot::GetIndex() const
{
	return Index;
}
