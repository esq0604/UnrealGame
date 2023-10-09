// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RetargetingTest/Public/Interface/Interactable.h"
#include "ItemBase.generated.h"

/**
 * 
 */
UENUM()
enum class EItemType : uint8
{
	ITEM_EQUIPMENT,
	ITEM_CONSUME,
};

class UBoxComponent;
class ACharacterBase;
UCLASS()
class RETARGETINGTEST_API AItemBase : public AActor
{
	GENERATED_BODY()

public:
	AItemBase();
	
	void AddReferenceSlot(class USlot*& Slot);
	void RemoveReferenceSlot(class USlot*& Slot);
	
	UTexture2D* GetThumbnail() const;
protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void OnPickup();
private:

public:

	UPROPERTY(EditAnywhere, Category="InteractableProperties")
	FString InteractableHelpText;
	UPROPERTY(EditAnywhere, Category="InteractableProperties")
	int32 Count;

	UPROPERTY(EditAnywhere,Category="ItemProperties")
	UTexture2D* PickupThumbnail;
	
	UPROPERTY(EditAnywhere,Category="ItemProperties")
	FString ItemName;
	
	UPROPERTY()
	TArray<USlot*> ReferenceSlot;

	UPROPERTY(EditAnywhere,Category="ItemType")
	EItemType ItemType;
	
protected:

};
