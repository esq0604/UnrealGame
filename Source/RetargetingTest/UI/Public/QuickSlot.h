// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuickSlot.generated.h"

/**
 * 
 */
class USlot;
class ACharacterBase;

UCLASS()
class RETARGETINGTEST_API UQuickSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Init();
	void Use(int index);

	void SetCharacter(ACharacterBase* NewCharacter);
	
protected:
	TArray<USlot*> Slots;
	ACharacterBase* Character;
private:
	const int MAX_QUICK_SLOT=4;
};
