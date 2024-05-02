// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/ItemDataAsset.h"
#include "InventoryComponent.generated.h"

class UQuickUI;
class UItemDataAsset;
class UEquipmentDataAsset;
enum class EItemType : uint8;
class UArmorDataAsset;
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
	bool AddItem(const UItemDataAsset* AddedItem);
	bool AddStartingItem();
	int32 HasEqualItem(FText ItemID,EItemType Type);
	UFUNCTION(BlueprintCallable)
	bool UseItem(EItemType Type,int32 Index);
	bool DropItem(EItemType Type, int32 Index);
	bool IsItemStackable(EItemType Type, int32 Index);
	bool IsItemInSlotValid(EItemType Type, int32 Index);
	
	//getter
	TArray<UItemDataAsset*>& GetItemsContainerRef(EItemType Type); 
	UItemDataAsset* GetItem(EItemType Type, int32 Index) ;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void UpdateInventoryUI(EItemType Type, int32 Index);
	void AddItemToIndex(UItemDataAsset* Item, int32 Index);
protected:

public:
	UPROPERTY(EditDefaultsOnly)
	int32 InventorySize=25;
	UPROPERTY(EditDefaultsOnly)
	int32 SlotPerRow = 5;

private:
	UPROPERTY()
	ACharacterBase* ComponentOwner;
	
	TWeakObjectPtr<UInventoryUI> InventoryUI;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true),Category="InventoryComponent | Inventory")
	TArray<UItemDataAsset*> ArmorItemsContainer;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true),Category="InventoryComponent | Inventory")
	TArray<UItemDataAsset*> WeaponItemsContainer;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true),Category="InventoryComponent | Inventory")
	TArray<UItemDataAsset*> ToolItemsContainer;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess=true),Category="InventoryComponent | Inventory")
	TArray<UItemDataAsset*> MagicItemsContainer;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess=true),Category="InventoryComponent | Inventory")
	TArray<UItemDataAsset*> QuestItemsContainer;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess=true),Category="InventoryComponent | Inventory")
	TArray<UItemDataAsset*> RingItemsContainer;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess=true),Category="InventoryComponent | Inventory")
	TArray<UItemDataAsset*> ShoesItemsContainer;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="InventoryComponent | StartingItems")
	TArray<UItemDataAsset*>	StartingItems;
};

