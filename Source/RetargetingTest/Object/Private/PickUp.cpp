// Fill out your copyright notice in the Description page of Project Settings.


#include "RetargetingTest/Object/Public/PickUp.h"

#include "Kismet/GameplayStatics.h"
#include "RetargetingTest/Player/Public/RetargetingTestCharacter.h"
#include "RetargetingTest/UI/Public/Slot.h"
#include "Engine/Texture2D.h"



APickUp::APickUp()
{
	//픽업을 위한 메시를 설정하고 아이템 이름, 도움말 및 아이템 값을 설정합니다.
	InteractableMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickupMesh");
	InteractableMesh->SetSimulatePhysics(true);
	ReferenceSlot.Init(nullptr,4);
	ItemName = FString("Enter an item name here...");
	InteractableHelpText=FString("Press E to pick item up.");
	Value=0;
}

void APickUp::BeginPlay()
{
	Super::BeginPlay();
}

void APickUp::Interact_Implementation()
{
	Super::Interact_Implementation();
	ARetargetingTestCharacter* Character=Cast<ARetargetingTestCharacter>(UGameplayStatics::GetPlayerCharacter(this,0));

	Character->AddItemToInventory(this);
	OnPickup();
}

/**
 * 아이템을 들고, 레벨에서 지워야할때 호출됩니다.
 * 아이템을 Distroy해버리면 , 캐릭터의 인벤토리에 아이템이 존재하지 않기때문에 지우지 않습니다.
 */
void APickUp::OnPickup()
{
	InteractableMesh->SetVisibility(false);
	InteractableMesh->SetSimulatePhysics(false);
	InteractableMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

EItemType APickUp::GetItemType() const
{
	return ItemType;
}

/**
 * 모든 아이템은 사용되기 때문에 자식에서 구현되어야 합니다.
 * ex) 포선 - 사용해서 체력을 채웁니다. , 총 - 사용하여 재장전하거나, 공격을 합니다
 * 아이템이 사용되면 현재 참조중인 슬롯에 변화가 생겨야합니다.
 */
void APickUp::Use_Implementation()
{
	GLog->Log("Use() from pickup class : YOU SOULD NOT BE SEEING THIS");
	
}

void APickUp::AddReferenceSlot(USlot*& Slot)
{
	ReferenceSlot.AddUnique(Slot);
}

void APickUp::RemoveReferenceSlot(USlot*& Slot)
{
	ReferenceSlot.RemoveSingle(Slot);
}

void APickUp::SwapReferenceSlot(APickUp* Item, int32 FromIndex, int32 ToIndex)
{
	const TArray<USlot*> From=ReferenceSlot;
	ReferenceSlot = Item->ReferenceSlot;
	Item->ReferenceSlot=From;

	// TArray<USlot*> QuickSlotList;
	// for(USlot* Slot : ReferenceSlot)
	// {
	// 	if(Slot->GetSlotType()==ESlotType::SLOT_QUICK)
	// 		QuickSlotList.Add(Slot);
	// }
	//
	// for(USlot* Slot : Item->ReferenceSlot)
	// {
	// 	if(Slot->GetSlotType()==ESlotType::SLOT_QUICK)
	// 		QuickSlotList.Add(Slot);
	// }
	//
	// for(USlot* Slot : QuickSlotList)
	// {
	// 	if(Slot->GetSlotIndex()==FromIndex)
	// 	{
	// 		this->ReferenceSlot.RemoveSingle(Slot);
	// 		Slot->SetIndex(ToIndex);
	// 		Item->ReferenceSlot.Add(Slot);
	// 	}
	// 	else
	// 	{
	// 		Item->ReferenceSlot.RemoveSingle(Slot);
	// 		Slot->SetIndex(FromIndex);
	// 		this->ReferenceSlot.Add(Slot);
	// 	}
	// }
}
