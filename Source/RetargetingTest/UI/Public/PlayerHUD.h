// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

class ARetargetingTestCharacter;
/**
 * 
 */
class UQuickSlot;
class UInventory;
class UPlayerGauge;

UCLASS()
class RETARGETINGTEST_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Init();
	
	UPlayerGauge* GetGauge() const;
	UQuickSlot* GetQuickSlot() const;
	UInventory* GetInventory() const;

	void SetCharacter(ARetargetingTestCharacter* NewCharater);
	void ToggleInventory();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (BindWidget))
	UPlayerGauge* Gauge;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (BindWidget))
	UQuickSlot* QuickSlot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (BindWidget))
	UInventory* Inventory;

	ARetargetingTestCharacter* Character;
};



