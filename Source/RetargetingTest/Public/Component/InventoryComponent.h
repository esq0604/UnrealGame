// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


enum class ESlotType : uint8;
enum class EEquipment_Type : uint8;
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
	bool AddItemToInventory(AItemBase* AddedItem);

	UFUNCTION(BlueprintCallable)
	bool AddItemToEquipments(AEquipmentItem* AddedItem);
	
	UFUNCTION(BlueprintCallable)
	void UseItemAtInventorySlot(int32 SlotNum);
	
	UFUNCTION(BlueprintCallable)
	void UseItemAtEquipmentSlot(EEquipment_Type EquipmentType);
	

	//getter
	AItemBase* GetItemAtInventory(int32 SlotNum) const;
	TArray<AItemBase*> GetInventory() const;
	TArray<AEquipmentItem*> GetEquipments() const;
	AEquipmentItem* GetItemAtEquipments(EEquipment_Type EquipmentType) const;
	UTexture2D* GetThumbnailAtInventorySlot(int32 SlotIdx) const;
	UTexture2D* GetThumbnailAtEquipment(EEquipment_Type EquipmentType) const;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess=true),Category="InventoryComponent | Inventory")
	TArray<AItemBase*> Inventory;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="InventoryComponent | Equipment")
	TArray<AEquipmentItem*> Equipments;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="InventoryComponent | StartingItems")
	TArray<TSubclassOf<AItemBase>> StartingInventoryItems;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(AllowPrivateAccess=true),Category="InventoryComponent | StartingItems")
	TArray<TSubclassOf<AEquipmentItem>> StartingEquipmentItems;
private:
	UPROPERTY()
	ACharacterBase* ComponentOwner;
	TWeakObjectPtr<UInventoryUI> InventoryUI;
	UEquipmentUI* EquipmentUI;
	const int NOT_INITIALIZED_SLOT=-1;

	
};
