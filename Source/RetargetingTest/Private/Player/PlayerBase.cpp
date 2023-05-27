// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerBase.h"

#include "MotionWarpingComponent.h"
#include "Component/InventoryComponent.h"
#include "Object/ItemBase.h"
#include "UI/Inventory.h"
#include "UI/PlayerHUD.h"
#include "UI/QuickSlot.h"
#include "UI/Slot.h"


class USlot;
// Sets default values
APlayerBase::APlayerBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void APlayerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/**
 * 라인트레이스를 이용해 인터렉터블 아이템이 있는지 확인합니다.
 */
AActor* APlayerBase::CheckForInteractalbe()
{
	FVector StartTrace = GetActorLocation();
	FVector EndTrace = GetActorLocation() + GetActorForwardVector() * 200.0f;

	FHitResult HitResult;

	FCollisionQueryParams CQP;
	CQP.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_WorldDynamic, CQP);

	
	AItemBase* PotentialInteractable = Cast<AItemBase>(HitResult.GetActor());

	
	DrawDebugLine(GetWorld(),
				  StartTrace,
				  EndTrace,
				  FColor::Red,
				  true,
				  1,
				  0,
				  2
	);
	if (PotentialInteractable == nullptr)
	{
		CurrentInteractable = nullptr;
		return nullptr;
	}
	else
	{
		CurrentInteractable = PotentialInteractable;
		return PotentialInteractable;
	}
}



/**
 *	TODO : 매번 전체 인벤토리를 Referesh하는건 비효율적입니다.
 *	현재 인터랙터블이 있는 경우 인터랙터블과 상호작용합니다.
 */
// void APlayerBase::Interact()
// {
// 	CheckForInteractalbe();
// 	if (CurrentInteractable != nullptr)
// 	{
// 		CurrentInteractable->Interact_Implementation();
// 		if (PlayerHUD->GetInventory() != nullptr)
// 		{
// 			PlayerHUD->GetInventory()->Refresh();
// 		}
// 	}
// }

/**
 * QuickSlot은 1,2,3,4번순으로 슬롯이 지정되어 있어. num을 넘겨줘 해당 슬롯을 사용하도록합니다
 *
 */
// void APlayerBase::UseQuickSlot(int UsedSlotIdx)
// {
// 	PlayerHUD->GetQuickSlot()->Use(UsedSlotIdx - 1);
// }

/**
 * TODO: 인벤토리의 UsealbeItem이 여러개일 경우를 생각해야합니다, 아이템을 사용시마다 인벤토리 전체를 초기화 하는건 비효율적입니다.
 * 아이템의 레퍼런스 슬롯을 받아 저장한 뒤, 사용 후 슬롯을 갱신합니다. 이때 인벤토리는 레퍼런스 슬롯에 들어가있지 않기때문에 인벤토리도 갱신합니다.
 * @param Slot - 인벤토리 슬롯의 인덱스가 들어옵니다.
 */
// void APlayerBase::UseItemAtInventorySlot(int32 Slot)
// {
// 	if (Inventory[Slot] != nullptr && Slot != -1)
// 	{
// 		TArray<USlot*> TempSlot;
//
// 		Inventory[Slot]->UseItem(this);
//
// 		//레퍼런스 슬롯이 없다면 인벤토리만 갱신합니다.
// 		if (Inventory[Slot]->ReferenceSlot.IsEmpty())
// 		{
// 			if (Inventory[Slot]->GetCount() == 0)
// 			{
// 				Inventory[Slot] = nullptr;
// 			}
// 			PlayerHUD->GetInventory()->GetSlot(Slot)->Refresh();
// 		}
// 		//있다면 레퍼런스 슬롯을 옮겨줍니다.
// 		else
// 		{
// 			for (USlot* eachSlot : Inventory[Slot]->ReferenceSlot)
// 			{
// 				TempSlot.Add(eachSlot);
// 			}
// 			if (Inventory[Slot]->GetCount() == 0)
// 			{
// 				Inventory[Slot] = nullptr;
// 			}
// 			for (USlot* eachSlot : TempSlot)
// 			{
// 				if (eachSlot != nullptr)
// 				{
// 					eachSlot->Refresh();
// 				}
// 			}
// 			PlayerHUD->GetInventory()->Refresh();
// 		}
// 	}
// }

/**
 * @param Item - 인벤토리에 들어갈 아이템이 들어옵니다.
 */
// bool APlayerBase::AddItemToInventory(AItemBase* Item)
// {
// 	if (Item != nullptr)
// 	{
// 		const int32 AvaliableSlot = Inventory.Find(nullptr);
// 		if (AvaliableSlot != INDEX_NONE)
// 		{
// 			Inventory[AvaliableSlot] = Item;
// 			return true;
// 		}
// 		else
// 		{
// 			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,TEXT("You cant carry any more items"));
// 		}
// 	}
// 	return false;
// }

// TArray<AItemBase*> APlayerBase::GetInventory() const
// {
// 	return Inventory;
// }

// AItemBase* APlayerBase::GetItemAtInventory(int32 Index)
// {
// 	return Inventory[Index];
// }

/**
* 슬롯에 있는 아이템의 썸네일을 반환합니다.
* @param Slot - 인벤토리 슬롯의 인덱스가 들어옵니다.
*/
// UTexture2D* APlayerBase::GetThumnailAtInventorySlot(int32 Slot) const
// {
// 	if (Inventory[Slot] != nullptr)
// 	{
// 		return Inventory[Slot]->PickupThumbnail;
// 	}
// 	return nullptr;
// }

