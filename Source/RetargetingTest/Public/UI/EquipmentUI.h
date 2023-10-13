// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipmentUI.generated.h"

class UInventoryComponent;
class UEquipmentSlot;
enum class EEquipment_Type : uint8;
class UButton;

/**
 * 
 */

UCLASS()
class RETARGETINGTEST_API UEquipmentUI : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init();
	void SlotInit(UEquipmentSlot* EquipSlot);
	virtual bool Initialize() override;
	
	void RefreshAllSlot();
	void RefreshSlotByIndex(int32 Index);
	void RefreshSlotByEquipmentType(EEquipment_Type Type);
	void SetInventoryComponent(UInventoryComponent* NewInventoryComponent);
	UEquipmentSlot* GetSlot(EEquipment_Type Type);
protected:
	virtual void NativeConstruct() override; 
private:
	UFUNCTION()
	void CloseButtonClicked();

protected:
	UPROPERTY()
	UInventoryComponent* InventoryComponent;
	
	UPROPERTY()
	TArray<UEquipmentSlot*> Slots;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(BindWidget),meta=(AllowPrivateAccess=true))
	UEquipmentSlot* WeaponSlot;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(BindWidget),meta=(AllowPrivateAccess=true))
	UEquipmentSlot* HeadSlot;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(BindWidget),meta=(AllowPrivateAccess=true))
	UEquipmentSlot* ArmorSlot;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(BindWidget),meta=(AllowPrivateAccess=true))
	UEquipmentSlot* PantsSlot;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(BindWidget))
	UButton* CloseButton;
};
