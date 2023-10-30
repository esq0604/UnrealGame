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
	bool UseItem(EItemType Type,int32 Index);
	
	bool IsItemStackable(int32 Index);
	bool IsItemInSlotValid(int32 Index) const;

	int8 IndexNormalize(int32 Index);

	//getter
	TArray<UItemDataAsset*>& GetItemsRef(EItemType Type); 
	UItemDataAsset* GetItem(EItemType Type, int32 Index) ;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void UpdateSlot(EItemType Type, int32 Index);
protected:

	
private:
	UPROPERTY()
	ACharacterBase* ComponentOwner;
	
	TWeakObjectPtr<UInventoryUI> InventoryUI;

	UPROPERTY()
	UEquipmentUI* EquipmentUI;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true),Category="InventoryComponent | Inventory")
	TArray<UItemDataAsset*> ArmorItems;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true),Category="InventoryComponent | Inventory")
	TArray<UItemDataAsset*> WeaponItems;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true),Category="InventoryComponent | Inventory")
	TArray<UItemDataAsset*> ToolItems;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess=true),Category="InventoryComponent | Inventory")
	TArray<UItemDataAsset*> MagicItems;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess=true),Category="InventoryComponent | Inventory")
	TArray<UItemDataAsset*> QuestItems;
	
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="InventoryComponent | StartingItems")
	TArray<UItemDataAsset*> StartingItems;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="InventoryComponent | StartingItems")
	TArray<TSubclassOf<UItemDataAsset>> TestStartingItems;
};
