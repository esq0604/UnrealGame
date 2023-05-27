// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UInventory;
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
	bool AddItemToInventory(AItemBase* Item);

	UFUNCTION(BlueprintCallable)
	void UseItemAtInventorySlot(int32 SlotNum);

	AItemBase* GetItemAtInventory(int32 SlotNum) const;
	TArray<AItemBase*> GetInventory() const;
	UTexture2D* GetThumbnailAtInventorySlot(int32 SlotIdx) const;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess=true),Category="InventoryComponent | Inventory")
	TArray<AItemBase*> Inventory;
	
private:
	ACharacterBase* ComponentOwner;
	
	UInventory* InventoryUI;
};
