// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuickSlot.generated.h"

/**
 * 
 */
class USlot;

UCLASS()
class RETARGETINGTEST_API UQuickSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Init();
	void Use(int index);
protected:
	TArray<USlot*> Slots;
	class ARetargetingTestCharacter* Character;
private:
	const int MAX_QUICK_SLOT=4;
};
