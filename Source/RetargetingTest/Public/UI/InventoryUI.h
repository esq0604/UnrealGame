// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryUI.generated.h"

enum class EItemType : uint8;
class UUniformGridPanel;
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

	//function
	void RefreshAllSlot();
	void RefreshSlotByIndex(int32 Index);
	void RemoveItem(EItemType ItemType,int32 Index);
	void HideAmountText(EItemType ItemType, int32 Index);
	//setter
	void SetTexture(EItemType ItemType,int32 Index,UTexture2D* InTexture);
	void SetAmountText(EItemType ItemType, int32 Index, int32 Quantity);
	void SetInventoryComponent(UInventoryComponent* NewInventoryComponent);

	USlot* GetSlot(EItemType Type,int32 Index) const;
	TArray<USlot*> GetSlots(EItemType Type) const;
	int32 GetEmptySlotIndex(EItemType Type) const;
protected:
	virtual void NativeConstruct() override; 

	UPROPERTY()
	UInventoryComponent* InventoryComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	TArray<USlot*> ToolSlots;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	TArray<USlot*> WeaponSlots;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	TArray<USlot*> MagicSlots;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	TArray<USlot*> QuestSlots;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(BindWidget))
	TObjectPtr<UUniformGridPanel> ToolItemsPanel;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(BindWidget))
	TObjectPtr<UUniformGridPanel> ArmorItemsPanel;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(BindWidget))
	TObjectPtr<UUniformGridPanel> WeaponItemsPanel;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(BindWidget))
	TObjectPtr<UUniformGridPanel> QuestItemsPanel;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(BindWidget))
	TObjectPtr<UUniformGridPanel> MagicItemsPanel;

private:
	int8 MAX_SLOT_NUM=16;
};
