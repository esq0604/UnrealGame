// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RetargetingTest/Player/Public/RetargetingTestCharacter.h"
#include "Inventory.generated.h"

/**
 * 
 */
class USlot;

UCLASS()
class RETARGETINGTEST_API UInventory : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void Init();
	void Refresh();
protected:
	virtual void NativeConstruct() override; 

	ARetargetingTestCharacter* Character;
	TArray<USlot*> Slots;
};
