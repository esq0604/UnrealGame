// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

class UGaugeBar;
class APlayerBase;
class ACharacterBase;
/**
 * 
 */
class UQuickSlot;
class UInventory;
class UPlayerGauge;
enum class EGaugeType;

UCLASS()
class RETARGETINGTEST_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Init();

	virtual void NativeConstruct() override;
	UFUNCTION(BlueprintCallable)
	void ToggleInventory();


	UGaugeBar* GetGauge(EGaugeType Type) const;
	UQuickSlot* GetQuickSlot() const;
	UInventory* GetInventory() const;

	void SetGauge(UGaugeBar* NewGauge, EGaugeType Type);
	void SetQuickSlot(UQuickSlot* NewQuickSlot);
	void SetInventory(UInventory* NewInventory);
	void SetCharacter(ACharacter* NewPlayer);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (BindWidget))
	UGaugeBar* HPGauge;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (BindWidget))
	UGaugeBar* StaminaGauge;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (BindWidget))
	UQuickSlot* QuickSlot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (BindWidget))
	UInventory* Inventory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ACharacterBase* Player;
};
