// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

/**
 * 
 */

class UItemDataAsset;
class UBoxComponent;
class ACharacterBase;
UCLASS(Abstract)
class RETARGETINGTEST_API AItemBase : public AActor
{
	GENERATED_BODY()

public:
	AItemBase();
	void AddReferenceSlot(class USlot*& Slot);
	void RemoveReferenceSlot(class USlot*& Slot);
	UTexture2D* GetThumbnail() const;
	void SetItemData(UItemDataAsset* Data);
protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void OnPickup();
private:

public:
	UPROPERTY()
	TArray<USlot*> ReferenceSlot;

protected:
	UPROPERTY(EditDefaultsOnly,Category="Item | Component")
	UStaticMeshComponent* StaticMeshComponent;

private:

};
