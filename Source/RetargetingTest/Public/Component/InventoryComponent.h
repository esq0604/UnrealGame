// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UItemDataAsset;
class UEquipmentDataAsset;
enum class EItemType : uint8;
class UArmorDataAsset;
enum class ESlotType : uint8;
class AEquipmentItem;
class UEquipmentUI;
class UInventoryUI;
class AItemBase;
class ACharacterBase;
class UTexture2D;


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RETARGETINGTEST_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryComponent();

	UFUNCTION(BlueprintCallable)
	bool AddItem(UItemDataAsset* AddedItem);
	
	UFUNCTION(BlueprintCallable)
	void UseItem(int32 SlotNum);
	
	bool IsItemStackable(int32 Index);

	int8 IndexNormalize(int32 Index);
	
	//getter
	FORCEINLINE TArray<UItemDataAsset*> GetItems() const {return Items;}
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void UpdateSlot(int32 Index);
protected:

	
private:
	UPROPERTY()
	ACharacterBase* ComponentOwner;
	
	TWeakObjectPtr<UInventoryUI> InventoryUI;

	UPROPERTY()
	UEquipmentUI* EquipmentUI;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess=true),Category="InventoryComponent | Inventory")
	TArray<UItemDataAsset*> Items;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="InventoryComponent | StartingItems")
	TArray<UItemDataAsset*> StartingItems;
};
