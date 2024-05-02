// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuickSlotUI.generated.h"

class UInventoryComponent;
/**
 * 
 */
class USlot;
class UEquipmentSlot;
class ACharacterBase;

UCLASS()
class RETARGETINGTEST_API UQuickSlotUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Init();
	void Use();
	void SlotInit(USlot* InitSlot);
	void SetInventoryComponent(UInventoryComponent* NewInventoryComponent);

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void PlayChangeMagicSlotAnim();
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void PlayChangeItemSlotAnim();
protected:
	TArray<USlot*> Slots;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(BindWidget),meta=(AllowPrivateAccess=true))
	UEquipmentSlot* RightHandSlot;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(BindWidget),meta=(AllowPrivateAccess=true))
	UEquipmentSlot* LeftHandSlot;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(BindWidget),meta=(AllowPrivateAccess=true))
	USlot* MainItemSlot;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(BindWidget),meta=(AllowPrivateAccess=true))
	USlot* SubItemSlot;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(BindWidget),meta=(AllowPrivateAccess=true))
	USlot* MainMagicSlot;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	int CurrentActionSlot{MAIN_ITEM_SLOT};
private:
	UPROPERTY()
	UInventoryComponent* InventoryComponent;
	const int MAX_QUICK_SLOT=5;
	const int EQUIP_QUICK_SLOT=-1;
	const int MAIN_ITEM_SLOT=0;
	const int SUB_ITEM_SLOT=1;
	const int MAIN_MAGIC_SLOT=3;
};
