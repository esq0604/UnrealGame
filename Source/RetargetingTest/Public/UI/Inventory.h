// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory.generated.h"

/**
 * 
 */
class APlayerBase;
class USlot;

UCLASS()
class RETARGETINGTEST_API UInventory : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void Init();
	
	void Refresh();
	void SetCharacter(APlayerBase* NewCharacter);
	USlot* GetSlot(int32 Index) const;
protected:
	virtual void NativeConstruct() override; 

	APlayerBase* Player;
	TArray<USlot*> Slots;
};
