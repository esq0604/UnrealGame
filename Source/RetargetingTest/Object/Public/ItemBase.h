// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RetargetingTest/Interface/Public/Interactable.h"
#include "ItemBase.generated.h"

/**
 * 
 */

class ARetargetingTestCharacter;
UCLASS()
class RETARGETINGTEST_API AItemBase : public AActor ,public IInteractable
{
	GENERATED_BODY()

public:
	AItemBase();

	virtual void Interact_Implementation() override;
	
	void OnPickup();
	
	void AddReferenceSlot(class USlot*& Slot);
	void RemoveReferenceSlot(class USlot*& Slot);
	virtual void UseItem(ARetargetingTestCharacter* Character) ;
	virtual int GetCount() const;
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
