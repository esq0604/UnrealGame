// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuickSlot.generated.h"

class UInventoryComponent;
/**
 * 
 */
class USlot;
class ACharacterBase;

UCLASS()
class RETARGETINGTEST_API UQuickSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Init();
	void Use(int index);

	void SetInventoryComponent(UInventoryComponent* NewInventoryComponent);

protected:
	TArray<USlot*> Slots;
private:
	UInventoryComponent* InventoryComponent;
	const int MAX_QUICK_SLOT=4;
};
