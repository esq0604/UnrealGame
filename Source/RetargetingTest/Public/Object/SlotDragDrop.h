// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "SlotDragDrop.generated.h"

/**
 * 
 */
class USlot;
class UInventoryComponent;

UCLASS()
class RETARGETINGTEST_API USlotDragDrop : public UDragDropOperation
{
	GENERATED_BODY()
public:
	bool Drop(USlot* To);
	bool SwapInven(USlot* to);
	bool SetQuickSlot(USlot* To);
	bool SwapQuickSlot(USlot* To);
	bool MoveQuickSlot(USlot* To);
	bool MoveEquipSlot(USlot* To);

	void SetFrom(USlot* NewFrom);
	void SetInventoryComponent(UInventoryComponent* NewInventoryComponent);
	
	USlot* GetFrom() const;
	
private:
	USlot* From;
	UInventoryComponent* InventoryComponent;	
};


