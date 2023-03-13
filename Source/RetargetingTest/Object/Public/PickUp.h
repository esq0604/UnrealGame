// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RetargetingTest/Object/Public/Interactable.h"
#include "PickUp.generated.h"

/**
 * 
 */
UENUM()
enum class EItemType : uint8
{
	ITEM_None,
	ITEM_Useable,
	ITEM_Equipmentable
};
UCLASS()
class RETARGETINGTEST_API APickUp : public AInteractable
{
	GENERATED_BODY()

public:
	APickUp();

	virtual void Interact_Implementation() override;
	
	void OnPickup();

	EItemType GetItemType() const;
	UFUNCTION(BlueprintNativeEvent)
	void Use();
	virtual void Use_Implementation();

	void AddReferenceSlot(class USlot*& slot);
	void RemoveReferenceSlot(class USlot*& slot);
	void SwapReferenceSlot(APickUp* item, int32 fromIndex, int32 toIndex);
protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere,Category="PickupProperties")
	UTexture2D* PickupThumbnail;
	
	UPROPERTY(EditAnywhere,Category="PickupProperties")
	int32 Value;

	UPROPERTY(EditAnywhere,Category="PickupProperties")
	FString ItemName;

private:
	UPROPERTY(EditAnywhere,Category="PickupProperties",meta=(AllowPrivateAccess=true))
	EItemType ItemType;

	UPROPERTY()
	TArray<class USlot*> ReferenceSlot;
};
