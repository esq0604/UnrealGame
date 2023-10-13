// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryUI.generated.h"

class UInventoryComponent;
/**
 * 
 */
class ACharacterBase;
class USlot;

UCLASS()
class RETARGETINGTEST_API UInventoryUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void Init();
	
	void RefreshAllSlot();
	void RefreshSlotByIndex(int32 Index);
	void SetInventoryComponent(UInventoryComponent* NewInventoryComponent);
	USlot* GetSlot(int32 Index) const;
protected:
	virtual void NativeConstruct() override; 

	UPROPERTY()
	UInventoryComponent* InventoryComponent;

	UPROPERTY()
	TArray<USlot*> Slots;
};
