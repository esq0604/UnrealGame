// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

class UEquipmentUI;
class UGaugeBar;
class APlayerBase;
class ACharacterBase;
/**
 * 
 */
class UQuickSlot;
class UInventoryUI;
enum class EGaugeType;

UCLASS()
class RETARGETINGTEST_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Init();

	virtual void NativeConstruct() override;

	UGaugeBar* GetGauge(EGaugeType Type) const;
	UQuickSlot* GetQuickSlot() const;
	
	void SetGauge(UGaugeBar* NewGauge, EGaugeType Type);
	void SetQuickSlot(UQuickSlot* NewQuickSlot);
	void SetCharacter(ACharacter* NewPlayer);
	
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (BindWidget))
	UGaugeBar* HPGauge;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (BindWidget))
	UGaugeBar* StaminaGauge;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (BindWidget))
	UQuickSlot* QuickSlot;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ACharacterBase* Player;


};
