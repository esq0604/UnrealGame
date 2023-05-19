// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryManagerComponent.generated.h"

class UInventory;
class AItemBase;
class ACharacterBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RETARGETINGTEST_API UInventoryManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryManagerComponent();

	bool AddItemToInventory(AItemBase* Item);
	void UseItemAtInventorySlot(int32 SlotNum);

	void SetOwnerInventory(TArray<AItemBase*>& NewInventory);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	ACharacterBase* ComponentOwner;
	TArray<AItemBase*> OwnerInventory;
	UInventory* InventoryUI;
};
