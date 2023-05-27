// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/InventoryComponent.h"
#include "RetargetingTest/Public/Interface/Interactable.h"
#include "ItemBase.generated.h"

/**
 * 
 */

class ACharacterBase;
UCLASS()
class RETARGETINGTEST_API AItemBase : public AActor ,public IInteractable
{
	GENERATED_BODY()

public:
	AItemBase();

	virtual void Interact_Implementation() override;

	UFUNCTION(BlueprintCallable)
	void OnPickup();
	
	void AddReferenceSlot(class USlot*& Slot);
	void RemoveReferenceSlot(class USlot*& Slot);
	virtual void UseItem(ACharacterBase* Character) ;
	virtual int GetCount() const;
	//void UseItem(ACharacterBase* Character);

	UTexture2D* GetThumbnail() const;
protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere, Category="InteractableProperties")
	class UStaticMeshComponent* InteractableMesh;
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
	
protected:

};
