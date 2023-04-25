// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory.generated.h"

/**
 * 
 */
class ACharacterBase;
class USlot;

UCLASS()
class RETARGETINGTEST_API UInventory : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void Init();
	
	void Refresh();
	void SetCharacter(ACharacterBase* NewCharacter);
	USlot* GetSlot(int32 Index) const;
protected:
	virtual void NativeConstruct() override; 

	ACharacterBase* Character;
	TArray<USlot*> Slots;
};
