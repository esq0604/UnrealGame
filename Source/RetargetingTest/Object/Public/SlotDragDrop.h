// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "SlotDragDrop.generated.h"

/**
 * 
 */
class USlot;

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
public:
	USlot* From;
	class ACharacterBase* Character;
};


