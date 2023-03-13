// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "SlotDragDrop.generated.h"

/**
 * 
 */
UCLASS()
class RETARGETINGTEST_API USlotDragDrop : public UDragDropOperation
{
	GENERATED_BODY()

public:
	bool Drop(class USlot* to);
	bool SwapInven(class USlot* to);
public:
	class USlot* From;
	class ARetargetingTestCharacter* Character;
};
