// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RetargetingTest/Object/Public/Interactable.h"
#include "PickUp.generated.h"

/**
 * 
 */

//TODO : APickUp 클래스는 아이템의 부모 클래스가 되어야합니다.
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

	void AddReferenceSlot(class USlot*& Slot);
	void RemoveReferenceSlot(class USlot*& Slot);
	void SwapReferenceSlot(APickUp* Item, int32 FromIndex, int32 ToIndex);

protected:
	virtual void BeginPlay() override;
public:      
	UPROPERTY(EditAnywhere,Category="PickupProperties")
	UTexture2D* PickupThumbnail;
	
	UPROPERTY(EditAnywhere,Category="PickupProperties")
	int32 Value;

	UPROPERTY(EditAnywhere,Category="PickupProperties")
	FString ItemName;
	
	//소비 아이템의 경우 개수가 있고, 장비아이템의 경우 개수가 없습니다.
	int Count;
	UPROPERTY()
	TArray<USlot*> ReferenceSlot;
private:
	UPROPERTY(EditAnywhere,Category="PickupProperties",meta=(AllowPrivateAccess=true))
	EItemType ItemType;


};
