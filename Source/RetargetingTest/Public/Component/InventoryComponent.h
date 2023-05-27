// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UInventory;
class AItemBase;
class ACharacterBase;

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

	void SetOwnerInventory(const TArray<AItemBase*>& NewInventory);

	TArray<AItemBase*> GetInventory() const;
	UTexture2D* GetThumnailAtInventorySlot(int32 SlotIdx);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess=true),Category="CharacterBase | Inventory")
	TArray<AItemBase*> Inventory;
	
private:
	ACharacterBase* ComponentOwner;
	
	UInventory* InventoryUI;
};
